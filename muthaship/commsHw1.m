clc
clear
close all

kVals = [2 4 6 8];


allConstPts = cell(size(kVals));
EbVals = zeros(length(kVals), 1);
nVals = zeros(length(kVals), 1);


for n = 1:4

    allConstPts{n} = genConstellationPts(kVals(n));
    
    disp(allConstPts{n});

end


for i = 1:4

    M = 2^kVals(i);

    sumSqVal = sum(abs(allConstPts{i}))/M;

    EbVals(i) = sumSqVal/kVals(i);

end

figure;

plot(kVals, EbVals, 'o-');
xlabel('k (Number of bits per symbol)');
ylabel('E_b (Energy per bit)');
title('Energy per Bit (E_b) vs. Number of Bits per Symbol (k)');
grid on;

for i = 1:4

    M = 2^kVals(i);

    nVals(i) = M/2;

end

figure;

plot(kVals, nVals, 'o-');
xlabel('k');
ylabel('n');
title('n vs. k');
grid on;

function constPts = genConstellationPts(k)
    
    constPtsQ1 = zeros((k/2)^2, 1);

    count = 1;
    
    for x = 1:k/2
        
        for y = 1:k/2
    
        constPtsQ1(count) = x + 1j*y;
    
        count = count+1;
    
        end
        
    end
    
    M = 2^k;
    
    A = 2 * sqrt(3 / (2 * (M - 1)));

    constPtsQ1 = (constPtsQ1 - (0.5 + 0.5j)) * A;
    
    constPts = [constPtsQ1; -1*constPtsQ1; conj(constPtsQ1); conj(-1*constPtsQ1)];

end


