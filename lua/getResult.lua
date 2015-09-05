
package.path = './?.lua;./lua/?.lua'
local parseJson = require('parseJson')
local pgsql = require('pgsql')
local rapidjson = require('rapidjson')

function  getResult(host,dbname,usr,pwd)
  conninfo = string.format("hostaddr=%s dbname=%s user=%s password=%s",host,dbname,usr,pwd)
  conn = pgsql.connectdb(conninfo)
  res = conn:exec("select getbydate('c016','2015-01-01','');")
  conn:clear()
  local restb = {}
  res = parseJson.parse(res)
  return res
end

--[[
local res = getResult("127.0.0.1","fasp_yz","postgres","postgres")
file = io.open('result-2.dat','w+')
file:write(res)
file:close()
--]]
--[[
json = '{"ason_086":null}'

value = rapidjson.decode(json)

print(getmetatable(value).__jsontype)

for k,v in pairs(value) do
  print (k,v)
  local tb = getmetatable(v)
  if ( tb == nil ) then
    print(type(v))
  else
    print(tb.__jsontype)
  end
  
end
--]]

--[[
local res = getResult("127.0.0.1","fasp_yz","postgres","postgres")
file = io.open('result.dat','w+')
file:write(res)
file:close()
--]]
