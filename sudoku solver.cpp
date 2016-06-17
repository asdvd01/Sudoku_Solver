#include<bits/stdc++.h>
#include<iostream>
#include<bitset>
#include<iomanip>
using namespace std;
class Sudoku{
	vector<int> row;
    vector<vector<int> > value;
    bitset<9> possibility[9][9];
    bool solvedFlag[9][9];
    public:
    void possibilities(int i,int j)
    {
    	int k;
    	cout<<"| ";
    	if(solvedFlag[i][j])
    		cout<<setw(11)<<value[i][j]+1;
    	else
    	{
    		cout<<"<";
    		for(k=0;k<9;k++)
    		{
    			if(possibility[i][j].test(k))
    			 cout<<(k+1);
    			else
    			 cout<<" ";
			}
			cout<<">";
		}
    	
	}
    void printposcount()
    {
    	int i,j;
        for(i=0;i<9;i++)
        {
        	cout<<"\t";
            for(j=0;j<9;j++)
            	possibilities(i,j);
            	cout<<"|\n\t---------------------------------------------------------------------------------------------------------------\n";
        }
	}
    void printAll()
    {
        int i,j,error=0;
        cout<<"\t+-----------------------------------+\n";
        for(i=0;i<9;i++)
        {
        	cout<<"\t";
            for(j=0;j<9;j++)
            {
            	if(value[i][j]!=-1)
            	error++;
            	if(j%3==0)
            		cout<<"| "<<value[i][j]+1<<" ";
            	else
            		cout<<"  "<<value[i][j]+1<<" ";
			}
            if(i%3==2)
            	cout<<"|\n\t+-----------+-----------+-----------+\n";
            else
            	cout<<" \n\t                                    \n";
        }
        cout<<"\n Solved upto "<<((float)error*100.0)/81.0<<"% \n";
    }
    void defaultvalue()
    {
        int i,j;
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                value[i][j]=-1;
                possibility[i][j].set();
                solvedFlag[i][j]=false;
            }
        }
    }
    void checkifsolved(int x,int y)
    {
    	int i;
        if(possibility[x][y].count()==1)
        {
            for (i=0; i<9; i++)
                if(possibility[x][y].test(i))
                    break;
            setVal(x,y,i);
        }
    }
    void checkNeighbour(int x,int y,int val)
    {
        int i,j;
        for(i=0;i<9;i++)
        {
            possibility[x][i].reset(val);
            if(!solvedFlag[x][i])
            checkifsolved(x,i);
            possibility[i][y].reset(val);
            if(!solvedFlag[i][y])
            checkifsolved(i,y);
        }
        int a=(x/3)*3;
        int b=(y/3)*3;
        for(i=a;i<(a+3);i++)
        {
            for(j=b;j<(b+3);j++)
            {
                possibility[i][j].reset(val);
                if(!solvedFlag[i][j])
                checkifsolved(i,j);
            }
        }
    }
    void setVal(int x,int y,int val)
    {
        value[x][y]=val;
        possibility[x][y].reset();
        solvedFlag[x][y]=true;
        checkNeighbour(x,y,val);
    }
    Sudoku(int n,vector<int> x,vector<int> y,vector<int> val)
    :row(9,0)
    ,value(9,row)
    {
        defaultvalue();
        int i;
        for(i=0;i<n;i++)
            setVal(x[i],y[i],val[i]);
    }
    Sudoku(vector<vector<int> > grid)
    :row(9,0)
    ,value(9,row)
    {
        defaultvalue();
        int i,j;
        for(i=0;i<9;i++)
        {
        	for(j=0;j<9;j++)
        	{
        		setVal(i,j,grid[i][j]-1);
			}
		}
    }
    void mat_ij(int x,int y)
    {
    	int i,j;
    	for(i=0;i<9;i++)
    	{
    		if(i!=y && solvedFlag[x][i] )
    		possibility[x][y].reset(value[x][i]);
    		if(i!=x && solvedFlag[i][y] )
    		possibility[x][y].reset(value[i][y]);
		}
		int a=(x/3)*3;
        int b=(y/3)*3;
        for(i=a;i<(a+3);i++)
        {
            for(j=b;j<(b+3);j++)
            {
            	if((i!=x || j!=y)&&(solvedFlag[i][j]))
            	{
                	possibility[x][y].reset(value[i][j]);
                }
            }
       }
	}
	void solveMedium()
	{
		int matx,maty,i,j,k;
		for(matx=0;matx<7;matx+=3)
		{
			for(maty=0;maty<7;maty+=3)
			{
				for(k=0;k<9;k++)
				{
					int px,py,c=0;
					for(i=matx;i<matx+3;i++)
					{
						for(j=maty;j<maty+3;j++)
						{
							if(!solvedFlag[i][j]&&possibility[i][j].test(k))
							{
								c++;
								px=i;
								py=j;
							}
						}
					}
					if(c==1)
					setVal(px,py,k);
				}
			}
		}
	}
    void solveEasy()
    {
    	int i,j;
    	for(i=0;i<9;i++)
    	{
    		for(j=0;j<9;j++)
    		{
    			if(!solvedFlag[i][j])
    			{
    				mat_ij(i,j);
    				checkifsolved(i,j);
				}
			}
		}
	}
};
main()
{
    int n,i;
    cout<<"Enter number of known values in Sudoku";
    cin>>n;
    cout<<"Enter Coordinates and values";
    vector<int> x(n),y(n),val(n);
    for(i=0;i<n;i++)
    {
        cin>>x[i]>>y[i]>>val[i];
        x[i]--;
        y[i]--;
        val[i]--;
    }
    Sudoku s1(n,x,y,val);
   // s1.printAll();
   // s1.solveEasy();
   // s1.printAll();
    s1.solveMedium();
   // s1.printAll();
   // s1.solveEasy();
    s1.printAll();
    s1.solveMedium();
    s1.printAll();
    s1.solveMedium();
    s1.printAll();
    s1.solveMedium();
    s1.printAll();
    cout<<"\n\n";
    //s1.printposcount();
}
