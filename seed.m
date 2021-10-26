if isoctave
  rand("state", 0)
else
  rng(0, 'twister')
end

disp(num2str(rand(1,3), '%12.6f'))
