function factshag(string1, string2, string3, string4, string5)
f = fopen(string2, "r");
shag = fscanf(f, "%i", [20 1])
fact = fscanf(f, "%lf", [20 1])
fclose(f);
f = fopen(string3, "r");
shag1 = fscanf(f, "%i", [20 1]);
fact1 = fscanf(f, "%lf", [20 1]);
fclose(f);
figure
semilogy (shag, fact);
hold on
grid on
semilogy(shag1, fact1);
title(string1);
xlabel("Шаг");
ylabel("Фактическая точность");
legend(string4, string5);
end