f = fopen("file1.txt", "r");
eps = fscanf(f, "%lf", [13 1])
%fact1 = fscanf(f, "%lf", [10 1]);
fact2 = fscanf(f, "%lf", [13 1])
%rung = fscanf(f, "%lf", [10 1]);
figure
%loglog (eps, fact1);
loglog (eps, fact2, 'r');
grid on
%loglog (eps, rung);
title("����������� �������� �� ��������");
xlabel("�������� �������� eps");
ylabel("����������� ��������");
%legend('S_2_h');