local pgsql = require('pgsql')
function  getResult(host,dbname,usr,pwd)
  conninfo = string.format("hostaddr=%s dbname=%s user=%s password=%s",host,dbname,usr,pwd)
  conn = pgsql.connectdb(conninfo)
  res = conn:exec("select getbydate('c016','2015-01-01','');")
  conn:clear()
  return res
end

--[[
local res = getResult("127.0.0.1","fasp_yz","postgres","postgres")
file = io.open('result.dat','w+')
file:write(res)
file:close()
--]]