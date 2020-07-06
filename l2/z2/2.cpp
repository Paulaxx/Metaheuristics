#include <iostream>
#include<cmath>
#include <vector>
#include <random>
#include<algorithm>
using namespace std;

typedef struct block{
    int i;
    int j;
    int p;
    int q;
    uint8_t value;
};

double calculate_distance(int **tab2, block **tab1, int n, int m){

    int i, j;
    double result = 0;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            result = result + pow(tab2[i][j] - tab1[i][j].value, 2);
        }
    }
    result = result / (n*m);
    return result;
}

void change(block **tab, vector<block> vect){
    int i, j, block_i, block_j, block_p, block_q, k;
    for(i=0;i<vect.size();i++){
        block_i = vect[i].i;
        block_j = vect[i].j;
        block_p = vect[i].p;
        block_q = vect[i].q;
        for(k=block_i;k<block_j;k++){
            for(j=block_p;j<block_q;j++){
                tab[k][j] = vect[i];
            }
        }
    }
}

bool operator==(const block& b1, const block& b2)
{
    if(b1.value == b2.value && b1.i == b2.i && b1.j == b2.j && b1.p == b2.p && b1.q == b2.q){
        return true;
    }
    return false;
}

vector<block> create_x0(block **tab, int n, int m, int k, vector<block> vect){

    int i, j, p, p2, x, i2, j2;
    uint8_t values[] = {0, 32, 64, 128, 160, 192, 223, 255};
    block b1;
    p = m;
    p2 = k;
    vector<int> columns_division;
    vector<int> rows_division;

    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 7);

    columns_division.push_back(0);
    while(p-p2 >= k){
        columns_division.push_back(p2);
        p2 = p2 + k;
    }
    columns_division.push_back(m);

    p = n;
    p2 = k;
    rows_division.push_back(0);
    while(p-p2 >= k){
        rows_division.push_back(p2);
        p2 = p2 + k;
    }
    rows_division.push_back(n);

    for(i=0;i<rows_division.size()-1;i++){
        b1.i = rows_division[i];
        b1.j = rows_division[i+1];
        for(j=0;j<columns_division.size()-1;j++){
             b1.p = columns_division[j];
             b1.q = columns_division[j+1];
             x = dist(rd);
             b1.value = values[x];
             vect.push_back(b1);
             for(i2=b1.i;i2<b1.j;i2++){
                 for(j2=b1.p;j2<b1.q;j2++){
                     tab[i2][j2] = b1;
                 }
             }
        }
    }
    return vect;
}

vector<block> change_value(block **tab, vector<block> vect){
    int l = vect.size(), random_block, new_value, i, j;
    uint8_t values[] = {0, 32, 64, 128, 160, 192, 223, 255};
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, l-1);
    std::uniform_int_distribution<int> dist2(0, 7);

    random_block = dist(rd);
    new_value = dist2(rd);
    block b = vect[random_block];
    b.value = values[new_value];
    vect[random_block] = b;

    for(i=b.i;i<b.j;i++){
        for(j=b.p;j<b.q;j++){
            tab[i][j].value = values[new_value];
        }
    }
    return vect;
}

vector<block> swap_blocks(block **tab, vector<block> vect){
    int l = vect.size(), b1, b2, i, j;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, l-1);
    std::uniform_int_distribution<int> dist2(0, l-1);
    b1 = dist(rd);
    b2 = dist2(rd);
    block block1 = vect[b1];
    block block2 = vect[b2];
    uint8_t temp;
    temp = block1.value;
    block1.value = block2.value;
    block2.value = temp;

    for(i=block1.i;i<block1.j;i++){
        for(j=block1.p;j<block1.q;j++){
            tab[i][j] = block1;
        }
    }
    for(i=block2.i;i<block2.j;i++){
        for(j=block2.p;j<block2.q;j++){
            tab[i][j] = block2;
        }
    }

    vect[b1] = block1;
    vect[b2] = block2;
    return vect;
}

vector<block> resize_block(block **tab, vector<block> vect, int n, int m, int k){
    int i,j, direction, btr=0, bloock, block_i, block_j, block_p, x=0, left_value, block_q, right_value;
    vector<block> blocks_to_resize;
    block selected_block, bigger;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 4);
    direction = dist(rd);
    switch(direction){
        case 1:{
            for(i=0;i<vect.size();i++){
                if((vect[i].q - vect[i].p - 1) >= k && vect[i].p != 0){
                    blocks_to_resize.push_back(vect[i]);
                    btr++;
                }
            }
            if(btr == 0)
                return vect;
            std::uniform_int_distribution<int> dist2(0, btr-1);
            bloock = dist2(rd);
            selected_block = blocks_to_resize[bloock];
            block_i = selected_block.i;
            block_j = selected_block.j;
            block_p = selected_block.p - 1;
            bigger = tab[block_i][block_p];
            if(block_i != bigger.i)
                x = -1;
            if(block_j != bigger.j)
                x = -1;
            if(x != -1){
                for(i=0;i<vect.size();i++){
                    if(vect[i] == bigger){
                        bigger.q = bigger.q + 1;
                        vect[i] = bigger;
                    }
                    else if(vect[i] == selected_block){
                        selected_block.p = selected_block.p + 1;
                        vect[i] = selected_block;
                    }
                }
            } else
                return vect;
            for(i=block_i;i<block_j;i++){
                tab[i][block_p+1] = bigger;
            }
            break;
        }
        case 2:{
            for(i=0;i<vect.size();i++){
                if((vect[i].q - vect[i].p - 1) >= k && vect[i].q != m){
                    blocks_to_resize.push_back(vect[i]);
                    btr++;
                }
            }
            if(btr == 0)
                return vect;
            std::uniform_int_distribution<int> dist2(0, btr-1);
            bloock = dist2(rd);
            selected_block = blocks_to_resize[bloock];
            block_i = selected_block.i;
            block_j = selected_block.j;
            block_q = selected_block.q;
            bigger = tab[block_i][block_q];
            if(block_i != bigger.i)
                x = -1;
            if(block_j != bigger.j)
                x = -1;
            if(x != -1){
                for(i=0;i<vect.size();i++){
                    if(vect[i] == bigger){
                        bigger.p = bigger.p - 1;
                        vect[i] = bigger;
                    }
                    else if(vect[i] == selected_block){
                        selected_block.q = selected_block.q - 1;
                        vect[i] = selected_block;
                    }
                }
            } else
                return vect;
            for(i=block_i;i<block_j;i++){
                tab[i][block_q-1] = bigger;
            }
            break;
        }
        case 3:{
            for(i=0;i<vect.size();i++){
                if((vect[i].j - vect[i].i - 1) >= k && vect[i].j != n){
                    blocks_to_resize.push_back(vect[i]);
                    btr++;
                }
            }
            if(btr == 0)
                return vect;
            std::uniform_int_distribution<int> dist2(0, btr-1);
            bloock = dist2(rd);
            selected_block = blocks_to_resize[bloock];
            block_q = selected_block.q;
            block_j = selected_block.j;
            block_p = selected_block.p;
            bigger = tab[block_j][block_p];
            if(block_p != bigger.p)
                x = -1;
            if(block_q != bigger.q)
                x = -1;
            if(x != -1){
                for(i=0;i<vect.size();i++){
                    if(vect[i] == bigger){
                        bigger.i = bigger.i - 1;
                        vect[i] = bigger;
                    }
                    else if(vect[i] == selected_block){
                        selected_block.j = selected_block.j - 1;
                        vect[i] = selected_block;
                    }
                }
            } else
                return vect;
            for(i=block_p;i<block_q;i++){
                tab[block_j - 1][i] = bigger;
            }
            break;
        }
        case 4:{
            for(i=0;i<vect.size();i++){
                if((vect[i].j - vect[i].i - 1) >= k && vect[i].i != 0){
                    blocks_to_resize.push_back(vect[i]);
                    btr++;
                }
            }
            if(btr == 0)
                return vect;
            std::uniform_int_distribution<int> dist2(0, btr-1);
            bloock = dist2(rd);
            selected_block = blocks_to_resize[bloock];
            block_q = selected_block.q;
            block_i = selected_block.i;
            block_p = selected_block.p;
            bigger = tab[block_i - 1][block_p];
            if(block_p != bigger.p)
                x = -1;
            if(block_q != bigger.q)
                x = -1;
            if(x != -1){
                for(i=0;i<vect.size();i++){
                    if(vect[i] == bigger){
                        bigger.j = bigger.j + 1;
                        vect[i] = bigger;
                    }
                    else if(vect[i] == selected_block){
                        selected_block.i = selected_block.i + 1;
                        vect[i] = selected_block;
                    }
                }
            } else
                return vect;
            for(i=block_p;i<block_q;i++){
                tab[block_i][i] = bigger;
            }
            break;
        }
    }
    return vect;

}

vector<block> generate_candidate_solution(block **tab, vector<block> vect, int n, int m, int k){
    int i, j, option;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 3);
    option = dist(rd);
    switch(option){
        case 1:{
            vect = change_value(tab, vect);
            break;
        }
        case 2:{
            vect = swap_blocks(tab, vect);
            break;
        }
        case 3:{
            vect = resize_block(tab, vect, n, m, k);
        }
    }
    return vect;
}

int main() {
    int t, n, m, k, i, j, repeat;
    double bestDistance, T, cooling = 0.99, actual_distance;
    std::random_device rd;
    std::uniform_real_distribution<double> dist(0, 1);

    vector<block> vect;
    vector<block> best_vec;
    cin>>t>>n>>m>>k;
    repeat = n * m;
    T = n * m;
    int ** M = new int * [n];
    for (i = 0; i<n; i++)
        M[i] = new int[m];

    uint8_t ** show = new uint8_t * [n];
    for (i = 0; i<n; i++)
        show[i] = new uint8_t[m];

    block ** M2 = new block * [n];
    for (i = 0; i<n; i++)
        M2[i] = new block[m];

    block ** best_m = new block * [n];
    for (i = 0; i<n; i++)
        best_m[i] = new block[m];

    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            cin>>M[i][j];
        }
    }

    vect = create_x0(M2, n, m, k, vect);
    best_vec = vect;
    std::copy(&M2[0][0], &M2[0][0]+n*m,&best_m[0][0]);
    bestDistance = calculate_distance(M, M2, n, m);

    clock_t start = clock();
    while((clock()-start)/CLOCKS_PER_SEC < t){

        for(i=0;i<repeat;i++){
            if((clock()-start)/CLOCKS_PER_SEC >= t)
                break;
            vect = generate_candidate_solution(M2, vect, n, m, k);
            actual_distance = calculate_distance(M, M2, n, m);
            if(actual_distance - bestDistance < 0){
                bestDistance = actual_distance;
                best_vec = vect;
            }
            else if(dist(rd) < exp((bestDistance - actual_distance)/T)){
                bestDistance = actual_distance;
                best_vec = vect;
            }
            else{
                vect = best_vec;
                change(M2, best_vec);
            }
        }
        T = T * cooling;
    }

    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            show[i][j] = M2[i][j].value;
        }
    }

    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            fprintf(stderr, "%d ", show[i][j]);
        }
        fprintf(stderr, "\n");
    }
    cout<<bestDistance<<endl;
    return 0;
}