#include <iostream>
#include <vector>
#include <stack>
#include <bitset>
using namespace std;



class Solution {
public:
	Solution():sqr(9),row(9),col(9){};
	static inline int c2i(char x){
		return x-'1';
	}
	static inline char i2c(int x){
		return x+'1';
	}
	static inline int SQR_I(int i, int j){
		i=i/3;
		j=j/3;
		return i*3+j;
	}
	void solveSudoku(vector<vector<char>>& board) {
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				if(board[i][j]!='.'){
					int x=c2i(board[i][j]);
					row[i].off(x);
					col[j].off(x);
					sqr[SQR_I(i,j)].off(x);
				} else{
					to_fill.push({i,j});
				}
			}
		}
		if (!bt(board))
			cout<<"unsolvable!\n";
		else
			cout<<"done!\n";
	}
	bool bt(vector<vector<char>>& board){
		if(!to_fill.empty()){
			auto cur=to_fill.top();
			int i=cur.first;
			int j=cur.second;
			avail inter=intersect(sqr[SQR_I(i,j)], row[i], col[j]);
			if(inter.empty()){//no available number
				return false;
			}
			to_fill.pop();
			for(auto& c:inter.iterate()){
				board[i][j]=c;
				sqr[SQR_I(i,j)].off(c);
				row[i].off(c);
				col[j].off(c);
				if(bt(board)) return true;
				sqr[SQR_I(i,j)].on(c);
				row[i].on(c);
				col[j].on(c);
			}
			to_fill.push(cur);
			return false;
		}
		return true;
	}

	struct avail{
		bitset<9> b;
		avail(){
			for(int i=0;i<9;i++)
				b[i]=true;
		}
		inline void off(int i){
			b[i]=false;
		}
		inline void on(int i){
			b[i]=true;
		}
		inline void off(char c){
			b[c2i(c)]=false;
		}
		inline void on(char c){
			b[c2i(c)]=true;
		}
		inline bool empty(){
			return b.none();
		}
		vector<char> iterate(){
			vector<char> ret;
			for(int x=0;x<9;x++){
				if(b[x]) ret.push_back(i2c(x));
			}
			return ret;
		}
	};
	static inline avail intersect(avail a, avail b, avail c){
		avail ret;
		ret.b=a.b & b.b & c.b;
		return ret;
	}
	
	/* bitset of unused numbers in each square
		0 1 2
		3 4 5
		6 7 8
	 */
	vector<avail> sqr;
	/* bitset of unused numbers in each row
		0
		1
		2
		.
		.
	 */
	vector<avail> row;
	/* bitset of unused numbers in each column
		0 1 2 . .
	 */
	vector<avail> col;
	//indexes of cells to fill
	stack<pair<int,int>> to_fill;
};


int main(){
	Solution s;
	vector<vector<char>> board(9,vector<char>{9});
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cin>>board[i][j];
		}
	}
	s.solveSudoku(board);
	cout<<"Solution:\n";
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout<<board[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}