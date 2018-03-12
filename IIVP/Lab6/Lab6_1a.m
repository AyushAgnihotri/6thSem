I = imread('Lenna.png');
I = rgb2gray(I);
grayLenna = I;

subplot(1,5,1),imshow(I);

I = double(grayLenna);

sigma = 1.76;

sz = 4;
[x,y]=meshgrid(-sz:sz,-sz:sz);

M = size(x,1)-1;
N = size(y,1)-1;
Exp_comp = -(x.^2+y.^2)/(2*sigma*sigma);
Kernel= exp(Exp_comp)/(2*pi*sigma*sigma);

Output = zeros(size(I));
I = padarray(I,[sz sz]);

for i = 1:(size(I,1)-M)
    for j =1:(size(I,2)-N)
        Temp = I(i:i+M,j:j+M).* Kernel;
        Output(i,j)=sum(Temp(:));
    end
end

Output = uint8(Output);

subplot(1,5,2),imshow(Output);

I = double(Output);

sigma = 1.76;

sz = 4;
[x,y]=meshgrid(-sz:sz,-sz:sz);

M = size(x,1)-1;
N = size(y,1)-1;
Exp_comp = -(x.^2+y.^2)/(2*sigma*sigma);
Kernel= exp(Exp_comp)/(2*pi*sigma*sigma);

Output = zeros(size(I));
I = padarray(I,[sz sz]);

for i = 1:(size(I,1)-M)
    for j =1:(size(I,2)-N)
        Temp = I(i:i+M,j:j+M).* Kernel;
        Output(i,j)=sum(Temp(:));
    end
end

Output = uint8(Output);
subplot(1,5,3),imshow(Output);

I = double(Output);

sigma = 1.76;

sz = 4;
[x,y]=meshgrid(-sz:sz,-sz:sz);

M = size(x,1)-1;
N = size(y,1)-1;
Exp_comp = -(x.^2+y.^2)/(2*sigma*sigma);
Kernel= exp(Exp_comp)/(2*pi*sigma*sigma);

Output = zeros(size(I));
I = padarray(I,[sz sz]);

for i = 1:(size(I,1)-M)
    for j =1:(size(I,2)-N)
        Temp = I(i:i+M,j:j+M).* Kernel;
        Output(i,j)=sum(Temp(:));
    end
end

Output = uint8(Output);
subplot(1,5,4),imshow(Output);

I = double(Output);

sigma = 1.76;

sz = 4;
[x,y]=meshgrid(-sz:sz,-sz:sz);

M = size(x,1)-1;
N = size(y,1)-1;
Exp_comp = -(x.^2+y.^2)/(2*sigma*sigma);
Kernel= exp(Exp_comp)/(2*pi*sigma*sigma);

Output = zeros(size(I));
I = padarray(I,[sz sz]);

for i = 1:(size(I,1)-M)
    for j =1:(size(I,2)-N)
        Temp = I(i:i+M,j:j+M).* Kernel;
        Output(i,j)=sum(Temp(:));
    end
end

Output = uint8(Output);
subplot(1,5,5),imshow(Output);

