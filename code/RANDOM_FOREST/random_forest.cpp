#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<math.h>
#include<list>
using namespace std;

#define REVIEWS 3900
#define TEST_REVIEWS 1670
#define ATTRIBUTES 89527
#define SEL_ATTRIBUTES 5000
#define THRESHOLD 0
#define FORESTS 5
#define FOREST_ATTRIBUTES 100

vector<string> Pos_Reviews;
vector<string> Neg_Reviews;
vector<string> Pos_Test_Reviews;
vector<string> Neg_Test_Reviews;
vector<vector<int> > Pos_Reviews_Matrix;
vector<vector<int> > Neg_Reviews_Matrix;
vector<int> Selected_Attributes;


void get_reviews(char inp_filename[], char out_filename[])
{
    ifstream ifile, ofile;
    // take output
    int cl;
    ifile.open(inp_filename);
    ofile.open(out_filename);
    string line("");
    int i=0;
    while (i<REVIEWS)
    {
        if(getline(ifile, line))
        {
            ofile>>cl;
            if(cl == 0)
                Pos_Reviews.push_back(line);
            else
                Neg_Reviews.push_back(line);
        }
        else
        {
            cout<<"Insufficient reviews in file\n";
            return;
        }
        i++;
    }
    ifile.close();
    ofile.close();
}


void get_test_reviews(char inp_filename[], char out_filename[])
{
    ifstream ifile, ofile;
    // take output
    int cl;
    ifile.open(inp_filename);
    ofile.open(out_filename);
    string line("");
    int i=0;
    while (i<TEST_REVIEWS)
    {
        if(getline(ifile, line))
        {
            ofile>>cl;
            if(cl == 0)
                Pos_Test_Reviews.push_back(line);
            else
                Neg_Test_Reviews.push_back(line);
        }
        else
        {
            cout<<"Insufficient reviews in file\n";
            return;
        }
        i++;
    }
    ifile.close();
    ofile.close();
}


inline int get_next_num(string &S, int &i)
{
    int num = 0;
    while(i<S.size() && !isdigit(S[i]))
    {
        i++;
    }
    if(i == S.size())
        return -1;
    while(i<S.size() && isdigit(S[i]))
    {
        num = num*10 + S[i]-'0';
        i++;
    }
    return num;
}

void create_reviews_matrix(vector<string> &Reviews, vector<vector<int> > &Reviews_Matrix)
{
    string S;
    int att_count;
    int total_reviews = Reviews.size();

    Reviews_Matrix.resize(total_reviews);
    for(int i=0;i<total_reviews;i++)
    {
        S = Reviews[i];
        int j=0;
        while(j<S.size())
        {
            att_count = get_next_num(S,j);
            if(att_count == -1)
                break;
            Reviews_Matrix[i].push_back(att_count);
        }
    }
}


struct review{
    int review_no;
    review *next;
    review(int num)
    {
      review_no = num;
      next = NULL;
    }
};

review* init_reviews(int num_reviews)
{
    review *start = new review(-1);
    review *curr = start;
    for(int i=0;i<num_reviews;i++)
    {
        curr->next = new review(i);
        curr = curr->next;
    }
    return start->next;
}


void select_attributes(int attr)
{
    Selected_Attributes.resize(attr);
    for(int i=0;i<attr;i++)
        Selected_Attributes[i] = i;
}

struct TreeNode
{
    int attrib, is_leaf;
    TreeNode *left, *right;
    TreeNode(int att, int leaf)
    {
        attrib = att;
        is_leaf = leaf;
        left = NULL;
        right = NULL;
    }
};


TreeNode* make_tree(review *pos_reviews, review *neg_reviews, list<int> &Avail_Attribs)
{
    if(pos_reviews == NULL) // make leaf and assign negative
    {
        TreeNode *temp = new TreeNode(-1, -1);
        //cout<<"-1";
        return temp;
    }
    if(neg_reviews == NULL) // make leaf and assign negative
    {
        TreeNode *temp = new TreeNode(-1, 1);
        //cout<<"1";
        return temp;
    }
    if(Avail_Attribs.size() == 0)
    {
        //make leaf and assign majority
        review *p = pos_reviews, *q = neg_reviews;
        while(p!=NULL && q!=NULL)
        {
            p = p->next;
            q = q->next;
        }
        if(p == NULL)
        {
            TreeNode *temp = new TreeNode(-1, -1);
            //cout<<"-1";
            return temp;
        }
        else
        {
            TreeNode *temp = new TreeNode(-1, 1);
            //cout<<"1";
            return temp;
        }
    }
    // chose best attribute min_it
    list<int>:: iterator it, min_it = Avail_Attribs.begin();
    int left_pos, left_neg, right_pos, right_neg, left, right, total;
    double min_entropy = 1, curr_entropy, entropy_left, entropy_right;
    for(it = Avail_Attribs.begin();it!=Avail_Attribs.end();it++)
    {
        left_pos = 0;
        left_neg = 0;
        right_pos = 0;
        right_neg = 0;
        review *curr = pos_reviews;
        while(curr!=NULL)
        {
            //if(curr->review_no == 1)
              // cout<<"see"<<THRESHOLD<<Pos_Reviews_Matrix[curr->review_no][*it]<<endl;
            if(Pos_Reviews_Matrix[curr->review_no][*it] > THRESHOLD)
            {
                 right_pos++;
            }
            else
                left_pos++;
            curr = curr->next;
        }
        curr = neg_reviews;
        while(curr!=NULL)
        {
            if(Neg_Reviews_Matrix[curr->review_no][*it] > THRESHOLD)
                right_neg++;
            else
                left_neg++;
            curr = curr->next;
        }
        left = left_pos + left_neg;
        right = right_pos + right_neg;
        total = left + right;
        //cout<<"left = "<<left_pos<<" "<<left_neg<<" "<<right_pos<<" "<<right_neg<<endl;
        if(!left || !right)
        {
            continue;
        }
        if(!left_pos || !left_neg)
            entropy_left = 0;
        else
            entropy_left = ((double)left_pos/left)*log2((double)left/left_pos) + ((double)left_neg/left)*log2((double)left/left_neg);
        if(!right_pos || !right_neg)
            entropy_right = 0;
        else
            entropy_right = ((double)right_pos/right)*log2((double)right/right_pos) + ((double)right_neg/right)*log2((double)right/right_neg);
        curr_entropy = ((double)left/total)*entropy_left + ((double)right/total)*entropy_right;
        if(curr_entropy < min_entropy)
        {
            min_entropy = curr_entropy;
            min_it = it;
        }
        //cout<<"ce "<<curr_entropy<<endl;
    }

    //cout<<"me "<<min_entropy<<endl;
    if(min_entropy == 1)
    {
        // make leaf and assign majority
        review *p = pos_reviews, *q = neg_reviews;
        while(p!=NULL && q!=NULL)
        {
            p = p->next;
            q = q->next;
        }
        if(p == NULL)
        {
            TreeNode *temp = new TreeNode(-1, -1);
            //cout<<"-1";
            return temp;
        }
        else
        {
            TreeNode *temp = new TreeNode(-1, 1);
            //cout<<"1";
            return temp;
        }
    }

    // partition lists into left pos, left neg, rt pos, rt neg
    review *left_pos_reviews_start = new review(-1);
    review *left_neg_reviews_start = new review(-1);
    review *right_pos_reviews_start = new review(-1);
    review *right_neg_reviews_start = new review(-1);
    review *left_pos_reviews=left_pos_reviews_start, *left_neg_reviews=left_neg_reviews_start;
    review *right_pos_reviews=right_pos_reviews_start, *right_neg_reviews=right_neg_reviews_start;
    review *p = pos_reviews;
    //cout<<"*minit"<<*min_it<<endl;
    int ct = 0;
    while(p!=NULL)
    {
        if(Pos_Reviews_Matrix[p->review_no][*min_it] > THRESHOLD)
        {
             ct++;
             right_pos_reviews->next = p;
             right_pos_reviews=right_pos_reviews->next;
        }
        else
        {
             left_pos_reviews->next = p;
             left_pos_reviews=left_pos_reviews->next;
        }
        p = p->next;
    }
    p = neg_reviews;
    int ct2 = 0;
    while(p!=NULL)
    {
        if(Neg_Reviews_Matrix[p->review_no][*min_it] > THRESHOLD)
        {
             ct2++;
             right_neg_reviews->next = p;
             right_neg_reviews=right_neg_reviews->next;
        }
        else
        {
             left_neg_reviews->next = p;
             left_neg_reviews=left_neg_reviews->next;
        }
        p = p->next;
    }

    if((left_pos_reviews_start->next == NULL && left_neg_reviews_start->next == NULL) || (right_pos_reviews_start->next == NULL && right_neg_reviews_start->next == NULL)) // best info gain is 0
    {
        // make leaf and assign majority
        review *p = pos_reviews, *q = neg_reviews;
        while(p!=NULL && q!=NULL)
        {
            p = p->next;
            q = q->next;
        }
        if(p == NULL)
        {
            TreeNode *temp = new TreeNode(-1, -1);
            return temp;
        }
        else
        {
            TreeNode *temp = new TreeNode(-1, 1);
            return temp;
        }
    }
    //cout<<"ba"<<*it<<endl;
    // remove best attrib
    int rem = *min_it;
    //root_file<<rem<<" "<<min_entropy<<endl;
    Avail_Attribs.erase(min_it);
    TreeNode *root = new TreeNode(rem, 0);
    root->left = make_tree(left_pos_reviews_start->next, left_neg_reviews_start->next, Avail_Attribs);
    root->right = make_tree(right_pos_reviews_start->next, right_neg_reviews_start->next, Avail_Attribs);

    // add best attrib
    Avail_Attribs.push_back(rem);
    return root;
}



double test_accuracy(vector<TreeNode*> &Roots, vector<string> &Pos_Test_Reviews, vector<string> &Neg_Test_Reviews)
{
    int num_pos_reviews = Pos_Test_Reviews.size();
    int num_neg_reviews = Neg_Test_Reviews.size();
    int sel_attribs = Pos_Test_Reviews[0].size();
    //vector<vector<int> > Pos_Test_Reviews_Matrix(num_pos_reviews, vector<int> (sel_attribs,-1));
    //vector<vector<int> > Neg_Test_Reviews_Matrix(num_neg_reviews, vector<int> (sel_attribs,-1));
    vector<vector<int> > Pos_Test_Reviews_Matrix;
    vector<vector<int> > Neg_Test_Reviews_Matrix;

    create_reviews_matrix(Pos_Test_Reviews, Pos_Test_Reviews_Matrix);
    create_reviews_matrix(Neg_Test_Reviews, Neg_Test_Reviews_Matrix);

    int correct_pos = 0;
    int correct_neg = 0;
    int pos_votes, neg_votes;
    string S;
    TreeNode *temp = NULL;
    for(int i=0; i<num_pos_reviews; i++)
    {
        S = Pos_Test_Reviews[i];
        pos_votes = 0;
        neg_votes = 0;
        for(int j=0;j<FORESTS;j++)
        {
            temp = Roots[j];
            while(temp->is_leaf == 0)
            {
                if(Pos_Test_Reviews_Matrix[i][temp->attrib] > THRESHOLD)
                    temp = temp->right;
                else
                    temp = temp->left;
            }
            if(temp->is_leaf == 1)
                pos_votes++;
            else
                neg_votes++;
        }
        if(pos_votes > neg_votes)
            correct_pos++;
    }

    for(int i=0; i<num_neg_reviews; i++)
    {
        S = Neg_Test_Reviews[i];
        pos_votes = 0;
        neg_votes = 0;
        for(int j=0;j<FORESTS;j++)
        {
            temp = Roots[j];
            while(temp->is_leaf == 0)
            {
                if(Neg_Test_Reviews_Matrix[i][temp->attrib] > THRESHOLD)
                    temp = temp->right;
                else
                    temp = temp->left;
            }
            if(temp->is_leaf == 1)
                pos_votes++;
            else
                neg_votes++;
        }
        if(pos_votes < neg_votes)
            correct_neg++;
    }

    cout<<"correct pos = "<<correct_pos<<"/"<<num_pos_reviews<<endl;
    cout<<"correct neg = "<<correct_neg<<"/"<<num_neg_reviews<<endl;
    double accuracy = (double)(correct_pos+correct_neg)/(num_pos_reviews + num_neg_reviews)*100;
    return accuracy;
}

void tree_traversal(TreeNode *root, int &nodes, int &leaves)
{
    if(root == NULL)
        return;
    if(root->is_leaf != 0)
        leaves++;
    nodes++;
    tree_traversal(root->left, nodes, leaves);
    tree_traversal(root->right, nodes, leaves);
}

int main()
{
    get_reviews("super_reduced_examples_train.txt", "output_train.txt");

    random_shuffle(Pos_Reviews.begin(), Pos_Reviews.end());
    random_shuffle(Neg_Reviews.begin(), Neg_Reviews.end());

    //Pos_Reviews.resize(Neg_Reviews.size());
    create_reviews_matrix(Pos_Reviews, Pos_Reviews_Matrix);
    create_reviews_matrix(Neg_Reviews, Neg_Reviews_Matrix);

    int no_sel_attr = Pos_Reviews_Matrix[0].size();
    select_attributes(no_sel_attr);

    review *pos_reviews = init_reviews(Pos_Reviews.size());
    review *neg_reviews = init_reviews(Neg_Reviews.size());
    //cout<<"@"<<Pos_Reviews.size()<<" "<<Neg_Reviews.size()<<endl;

    vector<TreeNode*> Roots(FORESTS);
    for(int i=0;i<FORESTS;i++)
    {
        random_shuffle(Selected_Attributes.begin(), Selected_Attributes.end());
        list<int> Avail_Attribs;
        for(int j=0;j<FOREST_ATTRIBUTES;j++)
            Avail_Attribs.push_back(Selected_Attributes[j]);
        review *pos_reviews = init_reviews(Pos_Reviews.size()); // reviews destroyed in making tree
        review *neg_reviews = init_reviews(Neg_Reviews.size());
        Roots[i] = make_tree(pos_reviews, neg_reviews, Avail_Attribs);
    }


    get_test_reviews("super_reduced_examples_test.txt", "output_train.txt");
    double accuracy = test_accuracy(Roots, Pos_Test_Reviews, Neg_Test_Reviews);
    cout<<"\nAccuracy on test data : "<<accuracy<<endl;


    return 0;
}
