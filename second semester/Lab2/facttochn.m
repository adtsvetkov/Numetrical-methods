f = fopen("facttochn.txt", "r");
eps = fscanf(f, "%i", [8 1])
fact = fscanf(f, "%lf", [8 1])
fact1 = fscanf(f, "%lf", [8 1])
figure
semilogy (eps, fact);
hold on
grid on
semilogy(eps, fact1);
title("����������� �������� �� ����� �����");
xlabel("����� ����� N");
ylabel("����������� ��������");
legend("������� ��� ����", "������� � �����")
fclose(f);