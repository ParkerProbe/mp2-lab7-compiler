program Example;
const
  c1: double = -7,24423;
  c2: integer = -2;
  c3: integer = 1;
var
  num1: integer = 2;
  num2: double = 0.12;
  num3: double = -7,24423;
  num4: integer;
begin
  num4 := 2;
  num1 := 5;
  num2 := 20;
  write('Введите четное целое число');
  Read(num1);
  write('Введите вещественное число');
  Read(num3);
  if num1 mod 2 = 0 then
  begin
    if c1 == 20 then
    begin
      num3 := (num1-num2*5 div 2)/(d*2);
      write('Result = ', num1);
    end
    else
      write();
    write('1');
  end
  else
  begin
    write('2');
    Read(num3);
    if num3 == 20 then
    begin
      num2:=(num1-num2*5 div 2)/(d*2);
      write('3 = ', num2);
    end
    else
      if c1 == 10 then
        if num2 == 30 then
          write('4')
  end
end.