function New = Newthon_method(fun, df1, df2, a, b, str)

f=fopen('C:\Users\Deadpool\Desktop\числаки\Матлаб1\Лабка1\lab.csv','a');
fprintf(f, str);
fprintf(f, '%s%1.4f%s%1.4f%s\n','Промежуток: [', a,',', b, ']');
fprintf(f,'Точность;Количество итераций;Разность корней;Корень;Значение функции в точке;Абсолютная погрешность;Относительная погрешность\n');

if (abs(df1(a))>abs(df1(b)))
    m = abs(df1(b));
else m = abs(df1(a));
end

if (abs(df2(a))>abs(df2(b)))
    M = abs(df2(a));
else M = abs(df2(b));
end

for i = 1:1:9
    count = 0;
    eps = 10^(-i);
    x0 = a;
    if fun(x0)*df2(x0)<=0 x0=b;
    end
    c = x0-(fun(x0)./df1(x0));
    est = sqrt((2*eps*m)./M);
    while abs(c-x0)> est
        x0 = c;
        c = x0-(fun(x0)./df1(x0));
        count = count + 1;
    end
    t = fzero(fun, c);
    del = fzero(fun, c) - c;
    beta = (del./(fzero(fun, x0)))*100;
   fprintf(f,'%5s%d%s;%d;%1.6e;%2.10f;%1.10f;%1.6e;%1.6e\n', '10^(-', i, ')', count, abs(t-c), c, fun(c), del, beta);
end

%сравним с fzero
t = fzero(fun, c);
fprintf(f,'%s;%2.10f\n', 'Корень fzero:', t);

fclose(f);
end