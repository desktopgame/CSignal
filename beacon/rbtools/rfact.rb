def fact(n)
	if n == 0 then
	  1
	else
	  n * fact(n - 1)
	end
end
p fact(5)