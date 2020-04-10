function ch = Check(fun, df1, df2, a, b, str)
c = fun(a)*fun(b);
figure
plot(0, c, 'go');
grid on
title(str); %оформляем
xlabel('x') 
ylabel('y')
figure
r= a:0.01:b;
z= df1(r); %вызываем функцию из файла в той же директории
plot(r, z); %строим график            
hold on
grid on 
z1=df2(r);
plot(r, z1);
hold on
title(str); %оформляем
xlabel('x') 
ylabel('y')
legend('график первой производной', 'график второй производной'),2;
end