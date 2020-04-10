f = fopen("file1.txt", "r");
eps = fscanf(f, "%lf", [10 1])
fact = fscanf(f, "%lf", [10 1])
fact1 = fscanf(f, "%lf", [10 1])
x = 0.0000000001:0.0000001:0.1;
y = x;
figure
loglog (eps, fact1);
hold on
grid on
loglog(eps, fact);
title("Фактическая точность от заданной");
xlabel("eps");
ylabel("Фактическая точность");
legend("Рунге-Кутт 2 порядка", "Неявный метод Адамса 2 порядка")
fclose(f);