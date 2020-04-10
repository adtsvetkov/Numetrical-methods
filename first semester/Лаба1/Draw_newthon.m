function Dr = Draw_newthon(fun, df1, df2, a, b, str)
figure
N= 300;
x= linspace(a,b,N) %формирует линейный массив 1хN1, начальный элемент а1, конечный - b1
z= fun(x);
h1 = plot(x, z, 'k'); %строим график
title(str); %оформляем
xlabel('x') 
ylabel('y')
grid on
hold on
x1 = a:0.01:b;
y1 = x1;
h2 = plot(x1, y1, 'r--');
x0 = a;
if fun(x0)*df2(x0)<=0 x0=b;
end
c = x0-(fun(x0)./df1(x0));
newy = fun(c);
plot (c, newy, 'mx');
for i = 1:1:4
    x = linspace(a, c, N);
    y = fun(c)+df1(c)*(x-c);
    plot(x, y);
    c = (c*df1(c) - fun(c))/df1(c);
    newy = fun(c);
    plot (c, newy, 'mx');
    plot (c, 0, 'k*');
    plot ([c, c], [0, newy], 'g-.');
    hold on;
end
k = fzero(fun, 10);
h3 = plot(k, 0, 'co');
legend([h1 h2 h3], 'P(x)', 'y = 0', 'solution');
end