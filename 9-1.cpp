#include <iostream>  
#include<map>
#include<set>
#include <algorithm>
#include<cstdio>
#include<cstring> 
#include<cmath>
#define N 200 
using namespace std;  
 
int page[N];//ҳ�����ú� 
int block[N];//�����飬�ڴ� 
int dist[N][N];//��ʾ��i�η����ڴ��ʱ���ڴ��е�ҳ��j ���Ժ󱻷��ʵ���Сʱ�� 

int n;//ҳ�����úŸ��� 
int m;//��������Ŀ 
int page_max;//���ҳ��� 

int pre[N];//page[i]��page�е�����
int opt(){//���ҳ���û��㷨 
    int page_lack = 0;
    memset(pre, 0, sizeof(pre));
    memset(dist, 0x3f, sizeof(dist));
    memset(block, -1, sizeof(block));
    for(int i=n; i>=1; --i){
         for(int j=0; j<=page_max; ++j) 
             if(pre[j])
                dist[i][j] = pre[j] - i;
         pre[page[i]] = i; 
    }
    
    for(int i=1; i<=n; ++i){//��ʼ����ҳ�棬��ʼ���ڴ���û�з�ҳ 
        int j;
        int max_dist = 0, p; 
        for(j=1; j<=m; ++j){
            if(block[j] == -1){//�Ŀ�û�з���ҳ�棬��ֱ�ӷ���, ����ȱҳ 
                block[j] = page[i]; 
                cout<<"ҳ��"<<page[i]<<"�����ڴ棬ֱ�ӷ���������"<<j<<"��!"<<endl;
                page_lack++;
                break;
            } else if(block[j] == page[i])//ҳ������ڴ��� 
                break;
            
            if(max_dist < dist[i][block[j]]){
                max_dist = dist[i][block[j]];//˵��block[j] ��Ӧ��ҳ���Ժ�᳤ʱ�䲻���õ� 
                p = j;//block[] ��j��ҳ��ᱻ�滻�� 
            }
        }
        if(j > m){//��ʱ�ڴ��в����ڷ����µķ�ҳ������û���ҵ�page[i]��Ӧ�ķ�ҳ������������ҳ���滻 
             cout<<"ҳ��"<<page[i]<<"�����ڴ棬��������"<<p<<"�е�ҳ��" <<block[p]<<"�滻��!"<<endl;
             block[p] = page[i];
             page_lack++; 
        }
        cout<<"��ǰ�ڴ���ҳ������:"<<endl; 
        for(int k=1; k<=m; ++k)//�ڴ���ҳ�������� 
            cout<<block[k]<<" ";
        cout<<endl<<endl;
    }
    return page_lack;//����ȱҳ���� 
} 

int lru(){//������δʹ���㷨��opt�㷨��ֻ࣬������lru����ǰ���� opt����� 
    int page_lack = 0;
    memset(pre, 0, sizeof(pre));
    memset(dist, 0x3f, sizeof(dist));
    memset(block, -1, sizeof(block));
    for(int i=1; i<=n; ++i){
         for(int j=0; j<=page_max; ++j) 
             if(pre[j])
                dist[i][j] = i - pre[j];//��ǰҳ�����������ҳ�����һ�γ��������Ĳ�ֵ
         pre[page[i]] = i; 
    }
    
    for(int i=1; i<=n; ++i){//��ʼ����ҳ�棬��ʼ���ڴ���û�з�ҳ 
        int j;
        int max_dist = 0, p; 
        for(j=1; j<=m; ++j){
            if(block[j] == -1){//�ÿ�û�з���ҳ�棬��ֱ�ӷ���, ����ȱҳ 
                block[j] = page[i]; 
                cout<<"ҳ��"<<page[i]<<"�����ڴ棬ֱ�ӷ���������"<<j<<"��!"<<endl;
                page_lack++;
                break;
            } else if(block[j] == page[i])//ҳ������ڴ��� 
                break;
            
            if(max_dist < dist[i][block[j]]){
                max_dist = dist[i][block[j]];//˵��block[j] ��Ӧ��ҳ���Ժ�᳤ʱ�䲻���õ� 
                p = j;//block[] ��j��ҳ��ᱻ�滻�� 
            }
        }
        if(j > m){//��ʱ�ڴ��в����ڷ����µķ�ҳ������û���ҵ�page[i]��Ӧ�ķ�ҳ������������ҳ���滻 
             cout<<"ҳ��"<<page[i]<<"�����ڴ棬��������"<<p<<"�е�ҳ��" <<block[p]<<"�滻��!"<<endl;
             block[p] = page[i];
             page_lack++; 
        }
        cout<<"��ǰ�ڴ���ҳ������:"<<endl; 
        for(int k=1; k<=m; ++k)//�ڴ���ҳ�������� 
            cout<<block[k]<<" ";
        cout<<endl<<endl;
    }
    return page_lack;//����ȱҳ���� 
} 

set<int>page_set;
int fifo(){//�Ƚ��ȳ�ҳ���û��㷨
    int page_lack = 0; 
    memset(block, -1, sizeof(block));
    int index = 1;
    for(int i=1; i<=n; ++i){
        if(index > m) index = 1;
        set<int>::iterator it;
        it = page_set.find(page[i]);  
        if(it == page_set.end()){
            if(block[index] != -1)
                page_set.erase(block[index]);
            page_set.insert(page[i]);
            block[index++] = page[i];
            ++page_lack;
        } 
        for(int k=1; k<=m; ++k)
            cout<<block[k]<<" ";
        cout<<endl;
    } 
    return page_lack;
}

int nru[N];//��ʾ ������ i ���ʱ�򱻷��ʹ� 
int page_in_block[N];//ҳ�� i �� block���±����� 
int clock(){
    int index = 1;
    int page_lack = 0;
    memset(block, -1, sizeof(block));
    for(int i=1; i<=n; ++i){
        if(page_in_block[page[i]]){//���page[i]�Ѿ����ڴ��� 
            nru[page_in_block[page[i]]] = 1;//���±������������е�ҳ�汻���ʹ��� 
            cout<<endl<<"��"<<i<<"��: ҳ��"<<page[i]<<"�Ѿ�����������"<< page_in_block[page[i]] << "��!"<<endl;
        }
        else {
            while(true){
                if(index > m) index = 1;
                if(block[index] == -1) {
                    nru[index] = 1;
                    page_in_block[page[i]] = index;
                    block[index++] = page[i];
                    ++page_lack;
                    break;
                }
                if(block[index] == page[i]){
                    nru[index++] = 1;
                    break;
                } else {
                    if(nru[index] == 0){//�滻��ҳ�� 
                        nru[index] = 1;
                        page_in_block[block[index]] = 0;
                        cout<<endl<<"��"<<i<<"��: ������"<<index<<"�е�ҳ��"<< block[index] <<"���δ��ʹ�ã���Ҫ��ҳ��"<<page[i]<<"�滻!"<<endl;
                        page_in_block[page[i]] = index;
                        block[index++] = page[i];
                        ++page_lack;
                        break;
                    } else
                        nru[index++] = 0;
                }
            } 
        }
        for(int k=1; k<=m; ++k)    
            cout<<block[k]<<" ";
        cout<<endl;
    }
    return page_lack;
}

int main(){
	cout<<"������ҳ�����ͻ�������С��" ; 
    cin>>n>>m;
    for(int i=1; i<=n; ++i){ 
    	cout<<"ҳ��"<<i; 
        cin>>page[i];
        cout<<endl;
        page_max = max(page_max, page[i]) ;
    } 
     cout<<"optȱҳ�жϴ���:"<<opt()<<endl;
     cout<<"***********************************"<<endl;
     cout<<"lruȱҳ�жϴ���:"<<lru()<<endl;
     cout<<"***********************************"<<endl;
     cout<<"fifoȱҳ�жϴ���:"<<fifo()<<endl;
     cout<<"***********************************"<<endl;
     cout<<"clockȱҳ�жϴ���:"<<clock()<<endl;
     return 0;
} 