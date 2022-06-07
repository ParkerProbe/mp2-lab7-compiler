program Example;
const
  c1: double = -7.24423;
  c2: integer = -2;
  c3: integer = 1;
var
  num1: integer = 2;
  num2: double = 0.12;
  nUm3: double = -7.24423;
  NUM4: integer;
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
    if c1 = 20 then
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