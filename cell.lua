posix = {}
for i=1,1000 do
    posix[i] = {0, 0}
end

function move(x, y, ix, iy)
    
    if x - ix < 99 then
        x = x + 1
    end
    if x - ix > 40 then
        y = y + 1
    end


    return x, y
     
end