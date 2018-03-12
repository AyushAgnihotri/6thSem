I = imread('Lenna.png');
I = rgb2gray(I);
grayLenna = I;

subplot(1,4,1),imshow(I);

I = double(grayLenna);

sigma = 1.76;


sz = 4;
[x,y]=meshgrid(-sz:sz,-sz:sz);

M = size(x,1)-1;
N = size(y,1)-1;
Exp_comp = -(x.^2+y.^2)/(2*sigma*sigma);
Kernel= exp(Exp_comp)/(2*pi*sigma*sigma);

for k = 1:4
    Output = zeros(size(I));
    I = padarray(I,[sz sz]);

    for i = 1:(size(I,1)-M)
        for j =1:(size(I,2)-N)
            Temp = I(i:i+M,j:j+M).* Kernel;
            Output(i,j) = sum(Temp(:));
        end
    end

    Output = uint8(Output);
    subplot(1,5,k+1),imshow(Output);
end

padded=zeros(size(grayLenna)+2);
filtered=zeros(size(grayLenna));

for x = 1:size(grayLenna,1)
    for y = 1:size(grayLenna,2)
        padded(x+1, y+1) = grayLenna(x, y);
    end
end

for i = 1:size(padded,1)-2
    for j = 1:size(padded,2)-2
        window = zeros(25,1);
        k = 1;
        for x = 1:5
            for y = 1:5
                window(k) = padded(i+x-1, j+y-1);
                k = k+1;
            end
        end
       
        median = sort(window);
        
        filtered(i, j) = avg(13);
    end
end

subplot(2,1,1),imshow(filtered);