function ch = Check(fun, df1, df2, a, b, str)
c = fun(a)*fun(b);
figure
plot(0, c, 'go');
grid on
title(str); %���������
xlabel('x') 
ylabel('y')
figure
r= a:0.01:b;
z= df1(r); %�������� ������� �� ����� � ��� �� ����������
plot(r, z); %������ ������            
hold on
grid on 
z1=df2(r);
plot(r, z1);
hold on
title(str); %���������
xlabel('x') 
ylabel('y')
legend('������ ������ �����������', '������ ������ �����������'),2;
end