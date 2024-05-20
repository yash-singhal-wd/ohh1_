#include <bits/stdc++.h>

using namespace std;

void adj_helper_each_row(vector<vector<int>> &matrix){
    int m = matrix.size();
    int n = matrix[0].size();

    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j){
            if(matrix[i][j]==2) continue;
            else {
                if(j+1<n){
                    if(matrix[i][j]==matrix[i][j+1]){
                        if(j-1>=0){
                            matrix[i][j-1] = !matrix[i][j];
                        }
                        if(j+2<n){
                            matrix[i][j+2] = !matrix[i][j];
                        } 
                    }
                }
                if(j+2<n){
                    if(matrix[i][j]==matrix[i][j+2]){
                        matrix[i][j+1] = !matrix[i][j];
                    }
                }
            }
        }
    }
} 

void adj_helper_each_column(vector<vector<int>> &matrix){
    int m = matrix.size();
    int n = matrix[0].size();
    for(int j=0; j<n; ++j){
        for(int i=0; i<m; ++i){
            if(matrix[i][j]==2) continue;
            else {
                if(i+1<m){
                    if(matrix[i][j]==matrix[i+1][j]){
                        if(i-1>=0){
                            matrix[i-1][j] = !matrix[i][j];
                        }
                        if(i+2<m){
                            matrix[i+2][j] = !matrix[i][j];
                        }
                    }
                }
                if(i+2<m){
                    if(matrix[i][j]==matrix[i+2][j]){
                        matrix[i+1][j] = !matrix[i][j];
                    }
                }
            }
        }
    }
}

void complete_row_helper(vector<vector<int>> &matrix){
    int m = matrix.size();
    int n = matrix[0].size();

    for(int i=0; i<m; ++i){
        int count0 = 0;
        int count1 = 0;
        for(int j=0; j<n; ++j){
            if(matrix[i][j]==0) count0++;
            if(matrix[i][j]==1) count1++;
            if(count1==n/2){
                for(int k=0; k<n; ++k){
                    if(matrix[i][k]==2)
                        matrix[i][k] = 0;
                }
                break;
            }
            if(count0==n/2){
                for(int k=0; k<n; ++k){
                    if(matrix[i][k]==2)
                        matrix[i][k] = 1;
                }
                break;
            }
        }
    }
}

void complete_col_helper(vector<vector<int>> &matrix){
    int m = matrix.size();
    int n = matrix[0].size();

    for(int j=0; j<n; ++j){
        int count0 = 0;
        int count1 = 0;
        for(int i=0; i<m; ++i){
            if(matrix[i][j]==0) count0++;
            if(matrix[i][j]==1) count1++;
            if(count1==n/2){
                for(int k=0; k<n; ++k){
                    if(matrix[k][j]==2)
                        matrix[k][j] = 0;
                }
                break;
            }
            if(count0==n/2){
                for(int k=0; k<n; ++k){
                    if(matrix[k][j]==2)
                        matrix[k][j] = 1;
                }
                break;
            }
        }
    }
}

void fill_all_partial_rows( int complete_i, int partial_i, 
                            vector<vector<int>> &matrix){
    int n = matrix.size();
    int count = 0;

    //counting the number of matching boxes in partial and full rows - should be a difference of 2
    for(int i=0; i<n; ++i){
        if(matrix[complete_i][i]==matrix[partial_i][i])
            count++;
    }
    if(count == n-2){
        for(int i=0; i<n; ++i){
            if(matrix[complete_i][i]!=matrix[partial_i][i])
                matrix[partial_i][i] = !(matrix[complete_i][i]);
        }
    }
}

void row_similarity_checker(vector<vector<int>> &matrix){
    //get the indices of filled rows and rows with 2 boxes missing (partial rows)
    vector<int> full_rows, partial_rows;
    int m = matrix.size();
    int n = matrix[0].size();

    for(int i=0; i<m; ++i){
        int count = 0;
        for(int j=0; j<n; ++j){
            if(matrix[i][j]==0 || matrix[i][j]==1){
                count++;
            }
        }
        if(count==n) full_rows.emplace_back(i);
        if(count==n-2) partial_rows.emplace_back(i);
    }

    //now do similarity check between full and partial rows
    for(int i=0; i<partial_rows.size(); ++i){
        for(int j=0; j<full_rows.size(); ++j){
            fill_all_partial_rows(full_rows[j], partial_rows[i], matrix);
        }
    }
}

void fill_all_partial_cols(int complete_j, int partial_j, 
                            vector<vector<int>> &matrix) {
    int n = matrix.size();
    int count = 0;

    //counting the number of matching boxes in partial and full rows - should be a difference of 2
    for(int i=0; i<n; ++i){
        if(matrix[i][complete_j]==matrix[i][partial_j])
            count++;
    }
    if(count == n-2){
        for(int i=0; i<n; ++i){
            if(matrix[i][complete_j]!=matrix[i][partial_j])
                matrix[i][partial_j] = !(matrix[i][complete_j]);
        }
    }
}

void col_similarity_checker(vector<vector<int>> &matrix){
    //get all indices of full cols and cols with 2 boxes missing (partial cols)
    vector<int> full_cols, partial_cols;
    int m = matrix.size();
    int n = matrix[0].size();

    for(int j=0; j<n; ++j){
        int count = 0;
        for(int i=0; i<m; ++i){
            if(matrix[i][j]==0 || matrix[i][j]==1){
                count++;
            }
        }
        if(count==n) full_cols.emplace_back(j);
        if(count==n-2) partial_cols.push_back(j);
    }

    //now fill all partial columns
    for(int i=0; i<partial_cols.size(); ++i){
        for(int j=0; j<full_cols.size(); ++j){
            fill_all_partial_cols(full_cols[j], partial_cols[i], matrix);
        }
    }
}

void solve_ohhi(vector<vector<int>> &matrix){
    for(int i=0; i<50; ++i){
        //check row adjacency
        adj_helper_each_row(matrix);
        
        //check column adjacency
        adj_helper_each_column(matrix);
        
        //complete row based on rule #2 (max allowed is half of row size)
        complete_row_helper(matrix);

        //complete column based on rule #2 (max allowed is half of col size)
        complete_col_helper(matrix);

        //complete row based on rule #3 (similarity)
        row_similarity_checker(matrix);

        //complete col based on rule #3 (similarity)
        col_similarity_checker(matrix);
    }
}

int main(){
    cout << "Welcome to Ohh1 solution generator!" << endl;
    cout << "nxn matrix" << endl;
    
    int n;
    cout << "n: ";
    cin >> n;
    vector<int> row(n,0);
    vector<vector<int>> matrix(n,row);
    cout << "Input 0:\033[1;34mblue\033[0m, 1:\033[1;33myellow\033[0m and 2:\033[1;37mblank\033[0m." << endl;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cin >> matrix[i][j];
        }
    }

    solve_ohhi(matrix);
    cout << endl;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    // cout << "\033[1;34mbold red text\033[0m\n";
    return 1;
}