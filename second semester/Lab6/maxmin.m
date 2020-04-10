%f = fopen("file3.txt", "r");
f = fopen("file2.txt", "r");
eps = fscanf(f, "%lf", [10 1]);
min = fscanf(f, "%lf", [10 1]);
max = fscanf(f, "%lf", [10 1]);
figure
loglog (eps, min);
hold on
loglog (eps, max);
grid on
title("������������ � ����������� ����� ��������� ��� �������� ��������");
xlabel("eps");
ylabel("����� ���������");
legend('Min', 'Max');
fclose(f);