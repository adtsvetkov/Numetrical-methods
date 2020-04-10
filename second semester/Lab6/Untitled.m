x=0:0.00001:1.5;
%y1=1;
%y = 1./cos(x) + y1*((sin(x)./cos(x)))
y = sin(x)+cos(x)
figure
plot(x, y);