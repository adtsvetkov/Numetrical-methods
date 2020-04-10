function Bis = Bisection_method(fun, a, b, str)

f=fopen('C:\Users\Deadpool\Desktop\числаки\Матлаб1\Лабка1\lab.csv','a');
fprintf(f, str);
fprintf(f, '%s%1.4f%s%1.4f%s\n','Промежуток: [', a,',', b, ']');
fprintf(f,'Точность;Количество итераций;Разность корней;Корень;Значение функции в точке;Абсолютная погрешность;Относительная погрешность\n');

a1 = a;
b1 = b;

for i = 1:1:9
    count = 1;
    eps = 10^(-i);
    c = (a + b) / 2;
    while abs(b - a) > 2 * eps 
        count = count + 1;
        c = (a + b) / 2;
        if fun(c) == 0
            break
        end
        if fun(a) * fun(c) < 0
            b = c;
        end
        if fun(b) * fun(c) < 0
            a = c;
        end
    end
    a=a1;
    b=b1;
    t = fzero(fun, c);
    del = fzero(fun, c) - c;
    beta = (del./(fzero(fun, c)))*100;
    fprintf(f,'%5s%d%s;%d;%1.6e;%2.10f;%1.10f;%1.6e;%1.6e\n', '10^(-', i, ')', count, abs(t-c), c, fun(c), del, beta);
end

%сравним с fzero
t = fzero(fun, c);
fprintf(f,'%s;%2.10f\n', 'Корень fzero:', t);

fclose(f);
end