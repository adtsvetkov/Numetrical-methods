%f = fopen("file3.txt", "r");
f = fopen("file3.txt", "r");
eps = fscanf(f, "%lf", [10 1]);
min = fscanf(f, "%lf", [10 1]);
max = fscanf(f, "%lf", [10 1]);
figure
semilogx (eps, min);
hold on
semilogx (eps, max);
grid on
title("������������ � ����������� ����� ��������� ��� �������� ��������");
xlabel("eps");
ylabel("����� ���������");
legend('Min', 'Max');
fclose(f);