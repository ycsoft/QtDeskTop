
--module("parseJson",package.seeall)
parseJson = {}

local rapidjson = require('rapidjson')

function outObject(Obj)
  local result = ''
  
  for k,v in pairs(Obj) do
    local tb = getmetatable(v)
    local tp
    local tv = v
    if( tb == nil) then
      tp = type(v)
      if ( tp == "function") then
        tv = "（空值）"
      end
      
    else
      tp = tb.__jsontype
    end
    --print('outObject-type:',tp)
    if (tp ~= "object" and tp ~= "array") then
      if ( result == '') then
        result  = string.format("%s 是 %s",k,tv)
      else
        result = string.format("%s, %s 是 %s",result,k,tv)
      end
    elseif(tp == "object") then
      result = string.format("%s\n%s是:\n%s\n",result,k,outObject(tv))
    elseif (tp == "array") then
      result = string.format("%s\n%s分别是\n%s\n",result,k,outArray(tv))
    end
   end
   return result
end

function outArray(Array)
  local result = ''
  for _,v in pairs(Array) do
    local tb = getmetatable(v)
    local tp --= getmetatable(v).__jsontype
    local tv = v
    if ( tb == nil ) then
      tp = type(v)
      if ( tp == "function") then
        tv = "空值"
      end
      
    else
      tp = tb.__jsontype
    end
   -- print(string.format("outArray-type:%s\n",tp))
    if ( tp ~= "object" and tp ~= "array") then
      if( result == '') then
        result = string.format("%s ",tv)
      else
        result =  string.format("%s;%s",result,tv)
      end
    elseif ( tp == "object") then
      --print("outArray:",v)
      if ( result == '' ) then
        result = string.format("  %s",outObject(v))
      else
        result = string.format("%s;\n  %s",result,outObject(v))
      end
    elseif ( tp == "array") then
      result = string.format("%s\n%s",result,outArray(v))
      --result = string.format("%s %s\n",result,outArray(v))
    end
  end
  return result
end

function parseJson.parse(Json,res)
  local value = rapidjson.decode(Json)
  local tp = getmetatable(value).__jsontype
  --print(string.format('Type is:%s\n',tp))
  if ( tp == "object") then
    return outObject(value)
  elseif( tp =="array") then
    --print("parse Array\n")
    return outArray(value)
  end  
end


return parseJson