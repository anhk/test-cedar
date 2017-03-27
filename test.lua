

local cedar = require 'cedar'

if not cedar then
    print("ERROR.")
end


local c = cedar.new()
if not c then
    print("ERROR.")
end


cedar.update(c, "http://www.baidu.com/", 9999)
cedar.update(c, "http://www.baidu.com/a", 9989.899)
cedar.update(c, "http://www.sohu.com/", 9979)
cedar.update(c, "http://www.sina.com/", 9969)

local function dump(ret)

    if not ret then
        print("return nil")
    end

    if type(ret) == "number" then
        print(ret)
    elseif type(ret) == "table" then
        for _, v in ipairs(ret) do
            print(v)
        end
    end
end

local ret = cedar.match(c, "http://www.baidu.com/aaaa")
print("match http://www.baidu.com/aaaa")
dump(ret)

local ret = cedar.match(c, "http://www.sohu.com/384asd?asdkfh")
print("match http://www.sohu.com/384asd?asdkfh")
dump(ret)

local ret = cedar.match(c, "http://www.google.com/384asd?asdkfh")
print("match http://www.google.com/384asd?asdkfh")
dump(ret)


