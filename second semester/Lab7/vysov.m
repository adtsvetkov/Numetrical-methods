function vysov(string1, string2)
f = fopen(string2, "r");
eps = fscanf(f, "%lf", [10 1])
vysov = fscanf(f, "%i", [10 1])
figure
loglog (eps, vysov);
hold on
grid on
title(string1);
xlabel("eps");
ylabel("Количество вызовов функции правой части");
fclose(f);
end