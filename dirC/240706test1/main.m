function main(targetValue, precision)
    % Define constants
    MAX_SIZE = 100;
    MATRIX_SIZE = 8;

    % Initialize the database structure
    tDatabase.data = repmat(struct('coordinate_x', 0, 'coordinate_y', 0, 'index', 0, 'value', 0, 'isOriginal', false), 1, MAX_SIZE);
    tDatabase.totalNumber = 0;
    tDatabase.columnNumber = 0;

    % Load data from the file
    tDatabase = loadData('dataOriginal2.txt', tDatabase, MATRIX_SIZE, MAX_SIZE);

    % Calculate extended data
    calculateExtendedData(tDatabase, targetValue, precision);
end

function tDatabase = loadData(fileName, tDatabase, MATRIX_SIZE, MAX_SIZE)
    % Open the file for reading
    fid = fopen(fileName, 'r');
    if fid == -1
        error('Could not open file');
    end

    % Read the data from the file into the structure
    i = 0;
    columnNumber = 0;
    while ~feof(fid) && i < MAX_SIZE
        value = fscanf(fid, '%lf', 1);
        if ~isempty(value)
            tDatabase.data(i+1).value = value;
            tDatabase.data(i+1).index = i;
            tDatabase.data(i+1).isOriginal = true;
            tDatabase.data(i+1).coordinate_x = mod(i, MATRIX_SIZE) + 1;
            if tDatabase.data(i+1).coordinate_x == 0 && MATRIX_SIZE <= tDatabase.data(i+1).index
                columnNumber = columnNumber + 1;
            end
            tDatabase.data(i+1).coordinate_y = columnNumber + 1;
            i = i + 1;
        end
    end
    tDatabase.totalNumber = i;

    % Close the file
    fclose(fid);

    % Print the data to verify
    fprintf('Data read from the file:\n');
    for i = 1:tDatabase.totalNumber
        fprintf('%d/%d\tx:%d,y:%d %f\n', tDatabase.data(i).index, tDatabase.totalNumber, ...
                tDatabase.data(i).coordinate_x, tDatabase.data(i).coordinate_y, ...
                tDatabase.data(i).value);
    end
end

function calculateExtendedData(tDatabase, targetValue, precision)
    possibility = false;
    for i = 1:tDatabase.totalNumber
        for j = i+1:tDatabase.totalNumber
            sum = tDatabase.data(i).value + tDatabase.data(j).value;
            if precision == 0
                if floor(sum) <= targetValue && ceil(sum) >= targetValue
                    possibility = true;
                    fprintf('Optional component==>>(%d, %d):%f + (%d, %d):%f = %f\n', ...
                            tDatabase.data(i).coordinate_x, tDatabase.data(i).coordinate_y, ...
                            tDatabase.data(i).value, tDatabase.data(j).coordinate_x, ...
                            tDatabase.data(j).coordinate_y, tDatabase.data(j).value, sum);
                end
            else
                if (sum * (1 - precision) <= targetValue) && (sum * (1 + precision) >= targetValue)
                    possibility = true;
                    fprintf('Optional component==>>(%d, %d):%f + (%d, %d):%f = %f\n', ...
                            tDatabase.data(i).coordinate_x, tDatabase.data(i).coordinate_y, ...
                            tDatabase.data(i).value, tDatabase.data(j).coordinate_x, ...
                            tDatabase.data(j).coordinate_y, tDatabase.data(j).value, sum);
                end
            end
        end
    end

    if ~possibility
        fprintf('No match!\n');
    end
end
