f = fopen("facttochn.txt", "r");
eps = fscanf(f, "%i", [8 1])
fact = fscanf(f, "%lf", [8 1])
fact1 = fscanf(f, "%lf", [8 1])
figure
semilogy (eps, fact);
hold on
grid on
semilogy(eps, fact1);
title("Фактическая точность от числа узлов");
xlabel("Число узлов N");
ylabel("Фактическая точность");
legend("Функция без угла", "Функция с углом")
fclose(f);