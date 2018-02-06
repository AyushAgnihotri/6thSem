function y = intensity_change_50(x)
    if (x > 250)
        y = 250;
    elseif (x > 200)
        y = 200;
    elseif (x > 150)
        y = 150;
    elseif (x > 100)
        y = 100;
    elseif (x > 50)
        y = 50;
    else
        y = 0;
    end
end