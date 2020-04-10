function err = errors(string)
%считываем данные из файла
f=fopen(string,'r');
n = fscanf(f, '%i', [1 1]);
A = fscanf(f, '%lf', [n n]);
cond = fscanf(f, '%lf', [1 1])
b = fscanf(f, '%lf', [n 1]);
x = fscanf(f, '%lf', [n 1]);
newA = fscanf(f, '%lf', [n n]);
xA = fscanf(f, '%lf', [n 1]);
newb = fscanf(f, '%lf', [n 1]);
xb = fscanf(f, '%lf', [n 1]);
%cчитаем коэффицент для возмущений в b
delx = xb-x;
delb = newb-b;
k1 = (norm(delx, 2)*norm(b, 2))/(norm(x, 2)*norm(delb, 2))
%cчитаем коэффициент для возмущений в А
delA = newA-A;
delx = xA-x;
k2 = (norm(delx, 2)*norm(A, 2))/(norm(xA, 2)*norm(delA, 2))
fclose(f);
end