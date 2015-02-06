PossibleExits = {}
function InitMaze() 
    theMaze = {}
    for i = 0, MazeWidth do
        theMaze[i] = {}

        for j = 0, MazeHeight do
            theMaze[i][j] = 1 --Set everything to 1
        end
    end
    RandomDirectionBias = {1,2,3,4}
    RandomStart()
    
end

function RandomStart()
    local r;
	local c;
    
	repeat
		r = rand() % MAZEWIDTH;
	 until (r % 2 == 0);
    
	repeat
        c = rand() % MAZEHEIGHT;
	 until (c % 2 == 0);

	--Set the starting path to 0
	theMaze[r][c] = 0;
	x = r;
	z = c;
end

local function shuffleTable( t )
    local rand = math.random 
    assert( t, "shuffleTable() expected a table, got nil" )
    local iterations = #t
    local j
    
    for i = iterations, 2, -1 do
        j = rand(i)
        t[i], t[j] = t[j], t[i]
    end
end

function Carve(int x, int y)
    shuffleTable(RandomDirectionBias)
    for i = 0, i < table.getn(RandomDirectionBias), i++ do
        if RandomDirectionBias[i] == 1 then
			if x - 2 <= 0 then
			
				--//Save the location of the deadend to PossibleExits
				--Location theLocation;
				--theLocation.theArray = &theMaze[x][y];
				--theLocation.x = x;
				--theLocation.y = y;
				--theLocation.Delete = false;
				--PossibleExits.push_back(theLocation);
				goto continue
            end
			
			if theMaze[x - 2][y] != 0 then
				theMaze[x - 2][y] = 0
				theMaze[x - 1][y] = 0
				Carve(x - 2, y)
            end
        end
        if RandomDirectionBias[i] == 2 then
            if y + 2 >= MAZEWIDTH - 1 then
				--Location theLocation;
				--theLocation.theArray = &theMaze[x][y];
				--theLocation.x = x;
				--theLocation.y = y;
				--theLocation.Delete = false;
				--PossibleExits.push_back(theLocation);
				goto continue;
            end
            if theMaze[x][y + 2] != 0 then
				theMaze[x][y + 2] = 0
				theMaze[x][y + 1] = 0
				Carve(x, y + 2)
			 end
        end
        if RandomDirectionBias[i] == 3 then
            if x + 2 >= MazeHeight - 1 then
                --Location theLocation;
				--theLocation.theArray = &theMaze[x][y];
				--theLocation.x = x;
				--theLocation.y = y;
				--theLocation.Delete = false;
				--PossibleExits.push_back(theLocation);
                goto cotinue;
            end
            if theMaze[x + 2][y] != 0 then
                theMaze[x + 2][y] = 0
				theMaze[x + 1][y] = 0
				Carve(x + 2, y)
            end
        end
        if RandomDirectionBias[i] == 4 then
            if y - 2 <= 0 then 
                --Location theLocation;
				--theLocation.theArray = &theMaze[x][y];
				--theLocation.x = x;
				--theLocation.y = y;
				--theLocation.Delete = false;
				--PossibleExits.push_back(theLocation);
				goto continue
            end
            if theMaze[x][y - 2] != 0 then
                theMaze[x][y - 2] = 0
				theMaze[x][y - 1] = 0
				Carve(x, y - 2)
            end
        end
        ::continue::
    end
end
    
        
function FindPossibleExits
    