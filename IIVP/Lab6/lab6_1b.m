I = imread('Lenna.png');
grayLenna = rgb2gray(I);

padded=zeros(size(grayLenna)+2);
filtered=zeros(size(grayLenna));

for x = 1:size(noisyLenna,1)
    for y = 1:size(noisyLenna,2)
        padded(x+1, y+1)= noisyLenna(x, y);
    end
end

for i = 1:size(padded,1)-2
    for j = 1:size(padded,2)-2
        window = zeros(9,1);
        k = 1;
        for x = 1:3
            for y = 1:3
                window(k) = padded(i+x-1, j+y-1);
                k = k+1;
            end
        end
        
        filtered(i, j) = mean(window);
    end
end

filtered = uint8(filtered);

subplot(1,3,1),imshow(grayLenna);
subplot(1,3,3),imshow(filtered);