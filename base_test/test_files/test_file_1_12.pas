var 
  x,y:= 2;
  v:= 3;
begin
  begin { ошибка: операторные скобки должны использоваться по ветке then оператора if }
    if x>y then
      v := x;
      x := y;
      y := v
  end;
end.