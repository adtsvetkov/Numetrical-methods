f = fopen("file4.txt", "r");
x = fscanf(f, "%lf", [16 1])
y = fscanf(f, "%lf", [16 1])
figure
semilogy (x, y);
grid on
title("����������� ��� 0.001 � ��������� �������");
xlabel("x");
ylabel("100*(y_n_e_w-y)/y_n_e_w");
%legend('Min', 'Max');
fclose(f);