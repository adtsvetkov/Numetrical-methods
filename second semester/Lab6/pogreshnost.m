f = fopen("file3.txt", "r");
pogr = fscanf(f, "%lf", [10 1])
fact = fscanf(f, "%lf", [10 1])
figure
plot (pogr, fact);
title("����������� �������� �� ��������� �����������, ������� ����� ������");
xlabel("��������� �����������");
ylabel("����������� ��������");
fclose(f);