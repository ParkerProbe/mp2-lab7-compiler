program Example;
begin { Commentary}
  num4 := 2; 
  num1 := 5;
  num2 := 20;
  write('Input even number');
  read(num1);
  write('Input real number');
  read(num3);
  if num1 mod 2 = 0 then
  begin
    if c2 = -2 then
    begin
      num3 := (num1-c2*5 div num1)/(c1*2);
      write('Result = ', num1);
    end
    else
      write();
    write('1');
  end
  else
  begin
    write('2');
    read(num3);
    if num3 = 20.0 then
    begin
      num2:=(num1-num4*5 mod 2)/(c1*2);
      write('3 = ', num2);
    end
    else
      if c1 = 10 then
        if num2 = 30 then
          write('4');
  end
end.
{Program end}
{ In  pascal mod, div for integer only}