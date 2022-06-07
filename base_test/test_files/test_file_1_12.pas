program test1_12;
var 
  x : integer = 2;
  y : integer = 3;
begin { ошибка: лишний  begin}
  if x>y then
  begin
    begin
      v := x;
      x := y;
      y := v;
    end
end.