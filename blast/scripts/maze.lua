function fact (n)
    if n == 0 then
        return 1
    else
        return n * fact(n - 1)
    end
end

writeline('你好乐基')

while (true)
do
    if (getkey(65) == 1) then
        writeline(1)
    else
        writeline(0)
    end

    sleep(100)
end