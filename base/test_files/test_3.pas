program Example;
const
  c1: double = -7.24423;
  c2: integer = -2;
  c3: integer = 1;
var
  num1: integer = 2;
begin { Commentary}
  num1 := 5;
  write('Input even number');
  read(num1);
  if num1 mod 2 = 0 then
  begin
    write('1');
  end
  else
  begin
    write('2');
  end
end.
{Program end}
{ In  pascal mod, div for integer only}