#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>

struct stasiun{
	char *nama; // menggunakan pointer
};

struct node{
	int idval;
	char user[100];
	int berangkat;
	int tujuan;
	struct node *left;
	struct node *right;
};

void dijkstra(int adjacency[11][11], int vertex, int startnode, int endnode);
struct node *newdata(int idval, const char *user, int berangkat, int tujuan){
	struct node *data = malloc(sizeof(struct node));
	data->idval = idval;
    strcpy(data->user, user);
    data->berangkat = berangkat;
    data->tujuan = tujuan;
    data->left = data->right = 0;
    
    return data;
}

struct node *adddata(struct node *root, int idval, const char *user, int berangkat, int tujuan, int height){
	if (height<3){
		if(root==0){
			printf("\n---Add New Data Success---\n\n");
			return newdata(idval, user, berangkat, tujuan);
		}
	
		else{
			while(height<91){
				if(root->idval < idval){
					root->right=adddata(root->right,idval,user,berangkat,tujuan,height+1);
				}
				else if(root->idval > idval){
					root->left = adddata(root->left,idval,user,berangkat,tujuan,height+1);
				}	
				break;
			}
		}
	}
	else if(height==3){
		printf("\n\n---Maximum Tree Height is 90---");
	}
		
	return root;
}
struct node *search(struct node *root, int idval){
	if (root!=0) {
    	if(root->idval==idval){
			return root;
    	} 	
		else {
			struct node * tmp;
    		tmp = search(root->left, idval);
			if (tmp==0) {
        		tmp=search(root->right, idval);
			}
			return tmp;
    	}
	}
}

struct node *successor(struct node * root) {
	struct node * tmp = root;
	while (tmp && tmp -> right != NULL){
		tmp = tmp -> right;
	}
	return tmp;
}

struct node *buy(struct node * root, int idval){
	if (root == NULL) {
		return root;
	}
	if (idval < root -> idval) {
		root -> left = buy(root -> left, idval);
	} 
	else if (idval > root -> idval) {
		root -> right = buy(root -> right, idval);
	} 
	else {
		if (root -> left == NULL) {
		    struct node * tmp = root -> right;
		    printf("\tSt%d - %s sudah membayar\n\n\n", root -> idval, root -> user);
		    free(root);
    		return tmp;
		} 
		else if (root -> right == NULL) {
		    struct node * tmp = root -> left;
		    printf("\tSt%d - %s sudah membayar\n\n\n", root -> idval, root -> user);
		    free(root);
		    return tmp;
  		} 
		else {
		    struct node * tmp = successor(root -> right);
		    root -> idval = tmp -> idval;
		    root -> right = buy(root -> right, tmp -> idval);
		    printf("\tSt%d - %s sudah membayar\n\n\n", root -> idval, root -> user);
  		}
	}
	return root;
}

struct node *delete_data(struct node * root, int idval){
	if (root == NULL) {
		return root;
	}
	if (idval < root -> idval) {
		root -> left = delete_data(root -> left, idval);
	} 
	else if (idval > root -> idval) {
		root -> right = delete_data(root -> right, idval);
	} 
	else {
		if (root -> left == NULL) {
		    struct node * tmp = root -> right;
		    printf("\tSt%d - %s telah dihapus\n\n\n", root -> idval, root -> user);
		    free(root);
    		return tmp;
		} 
		else if (root -> right == NULL) {
		    struct node * tmp = root -> left;
		    printf("\tSt%d - %s telah dihapus\n\n\n", root -> idval, root -> user);
		    free(root);
		    return tmp;
  		} 
		else {
		    struct node * tmp = successor(root -> right);
		    root -> idval = tmp -> idval;
		    root -> right = delete_data(root -> right, tmp -> idval);
		    printf("\tSt%d - %s telah dihapus\n\n\n", root -> idval, root -> user);
  		}
	}
	return root;
}

void display(struct node *root){
	int vertex = 11;
	int adjacency[11][11]={ {0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
							{5, 0, 20, 0, 0, 0, 0, 0, 0, 10, 0}, 
							{0, 20, 0, 13, 0, 0, 0, 0, 0, 0, 0}, 
							{0, 0, 13, 0, 13, 0, 0, 0, 0, 0, 0}, 
							{0, 0, 0, 13, 0, 5, 20, 0, 0, 0, 0}, 
							{0, 0, 0, 0, 5, 0, 15, 0, 0, 0, 20}, 
							{0, 0, 0, 0, 20, 15, 0, 10, 0, 0, 0}, 
							{0, 0, 0, 0, 0, 0, 10, 0, 15, 0, 0}, 
							{0, 0, 0, 0, 0, 0, 0, 15, 0, 20, 0}, 
							{0, 10, 0, 0, 0, 0, 0, 0, 20, 0, 15}, 
							{0, 0, 0, 0, 0, 20, 0, 0, 0, 15, 0} };
	int startnode;
	int endnode;
	char namast[100];
	char namast2[100];
	struct stasiun st[100];
	
	st[0].nama = "Utta";
	st[1].nama = "Etogawa";
	st[2].nama = "Shiojiri";
	st[3].nama = "Otsuki";
	st[4].nama = "Chiba";
	st[5].nama = "Ueno";
	st[6].nama = "Shinagawa";
	st[7].nama = "Harajuku";
	st[8].nama = "Meguro";
	st[9].nama = "Shinjiku";
	st[10].nama = "Nikko";
	
	if(startnode==0){
		strcpy(namast,st[0].nama);
	}
	else if(startnode==1){
		strcpy(namast,st[1].nama);
	}
	else if(startnode==2){
		strcpy(namast,st[2].nama);
	}
	else if(startnode==3){
		strcpy(namast,st[3].nama);
	}
	else if(startnode==4){
		strcpy(namast,st[4].nama);
	}
	else if(startnode==5){
		strcpy(namast,st[5].nama);
	}
	else if(startnode==6){
		strcpy(namast,st[6].nama);
	}
	else if(startnode==7){
		strcpy(namast,st[7].nama);
	}
	else if(startnode==8){
		strcpy(namast,st[8].nama);
	}
	else if(startnode==9){
		strcpy(namast,st[9].nama);
	}
	else if(startnode==10){
		strcpy(namast,st[10].nama);
	}
	
	//
	if(endnode==0){
		strcpy(namast2,st[0].nama);
	}
	else if(endnode==1){
		strcpy(namast2,st[1].nama);
	}
	else if(endnode==2){
		strcpy(namast2,st[2].nama);
	}
	else if(endnode==3){
		strcpy(namast2,st[3].nama);
	}
	else if(endnode==4){
		strcpy(namast2,st[4].nama);
	}
	else if(endnode==5){
		strcpy(namast2,st[5].nama);
	}
	else if(endnode==6){
		strcpy(namast2,st[6].nama);
	}
	else if(endnode==7){
		strcpy(namast2,st[7].nama);
	}
	else if(endnode==8){
		strcpy(namast2,st[8].nama);
	}
	else if(endnode==9){
		strcpy(namast2,st[9].nama);
	}
	else if(endnode==10){
		strcpy(namast2,st[10].nama);
	}
	
    if(root==0){
    	return;
	}
	startnode = root->berangkat;
	endnode = root->tujuan;

    display(root->left);
    printf("\n=====================================================================\n");
    printf("Id Pelangan                = St %d\n",root->idval);
    printf("Nama pelanggan             = %s\n",root->user);
    printf("Stasiun Pemberangkatan     = Stasiun %s\n",st[startnode].nama);
    printf("Stasiun Tujuan             = Stasiun %s\n",st[endnode].nama);
    dijkstra(adjacency, vertex, root->berangkat, root->tujuan);
    display(root->right);
}
void dijkstra(int adjacency[11][11], int vertex, int startnode , int endnode){
	int temp[11][11], jarak[11], pred[11], visited[11];
	int count, jarakmin, nextnode, x, y;
	char namast[100];
	char namast2[100];
	struct stasiun st[100];
	st[0].nama = "Utta";
	st[1].nama = "Etogawa";
	st[2].nama = "Shiojiri";
	st[3].nama = "Otsuki";
	st[4].nama = "Chiba";
	st[5].nama = "Ueno";
	st[6].nama = "Shinagawa";
	st[7].nama = "Harajuku";
	st[8].nama = "Meguro";
	st[9].nama = "Shinjiku";
	st[10].nama = "Nikko";
	
	//berangkat
	if(startnode==0){
		strcpy(namast,st[0].nama);
	}
	else if(startnode==1){
		strcpy(namast,st[1].nama);
	}
	else if(startnode==2){
		strcpy(namast,st[2].nama);
	}
	else if(startnode==3){
		strcpy(namast,st[3].nama);
	}
	else if(startnode==4){
		strcpy(namast,st[4].nama);
	}
	else if(startnode==5){
		strcpy(namast,st[5].nama);
	}
	else if(startnode==6){
		strcpy(namast,st[6].nama);
	}
	else if(startnode==7){
		strcpy(namast,st[7].nama);
	}
	else if(startnode==8){
		strcpy(namast,st[8].nama);
	}
	else if(startnode==9){
		strcpy(namast,st[9].nama);
	}
	else if(startnode==10){
		strcpy(namast,st[10].nama);
	}
	
	//tujuan
	if(endnode==0){
		strcpy(namast2,st[0].nama);
	}
	else if(endnode==1){
		strcpy(namast2,st[1].nama);
	}
	else if(endnode==2){
		strcpy(namast2,st[2].nama);
	}
	else if(endnode==3){
		strcpy(namast2,st[3].nama);
	}
	else if(endnode==4){
		strcpy(namast2,st[4].nama);
	}
	else if(endnode==5){
		strcpy(namast2,st[5].nama);
	}
	else if(endnode==6){
		strcpy(namast2,st[6].nama);
	}
	else if(endnode==7){
		strcpy(namast2,st[7].nama);
	}
	else if(endnode==8){
		strcpy(namast2,st[8].nama);
	}
	else if(endnode==9){
		strcpy(namast2,st[9].nama);
	}
	else if(endnode==10){
		strcpy(namast2,st[10].nama);
	}
	
	
	for (x = 0; x < vertex; x++){
		for (y = 0; y < vertex; y++){
			if (adjacency[x][y] == 0){
				temp[x][y] = 9999;
			}
			else{
				temp[x][y] = adjacency[x][y];
			}
		}
	}
	for (x = 0; x < vertex; x++){
		jarak[x] = temp[startnode][x];
		pred[x] = startnode;
		visited[x] = 0;
	}
	jarak[startnode] = 0;
	visited[startnode] = 1;
	count = 1;
	while (count<vertex-1){
		jarakmin = 9999;
		for (x = 0; x < vertex; x++){
			if (jarak[x] < jarakmin && !visited[x]){
				jarakmin = jarak[x];
				nextnode = x;
			}
		}
		visited[nextnode] = 1;
		for (x = 0; x < vertex; x++){
			if (!visited[x]){
				if (jarakmin + temp[nextnode][x] < jarak[x]){
					jarak[x] = jarakmin + temp[nextnode][x];
					pred[x] = nextnode;
				}
			}
		}
		count++;
	}
	
	for (x = 0; x <= endnode; x++){
		if (x == endnode){
			printf("\nRute Stasiun = (%s)", st[x].nama);
			y = x;
			
			do{
				y = pred[y];
				printf(" <- (%s)", st[y].nama);
			}
			while(y != startnode);
			printf("\n\nJarak dari stasiun %s ke stasiun %s       = %dkm",namast, namast2, jarak[x]);
			printf("\nHarga tiket dari stasiun %s ke stasiun %s = Rp.%d",namast, namast2,500 * jarak[x]);
			printf("\n=====================================================================\n\n");
		}
	}
}

void pathfinder(int adjacency[11][11], int vertex, int startnode , int endnode){
	int temp[11][11], jarak[11], pred[11], visited[11];
	int count, jarakmin, nextnode, x, y;
	char namast[100];
	char namast2[100];
	struct stasiun st[100];
	st[0].nama = "Utta";
	st[1].nama = "Etogawa";
	st[2].nama = "Shiojiri";
	st[3].nama = "Otsuki";
	st[4].nama = "Chiba";
	st[5].nama = "Ueno";
	st[6].nama = "Shinagawa";
	st[7].nama = "Harajuku";
	st[8].nama = "Meguro";
	st[9].nama = "Shinjiku";
	st[10].nama = "Nikko";
	
	//berangkat
	if(startnode==0){
		strcpy(namast,st[0].nama);
	}
	else if(startnode==1){
		strcpy(namast,st[1].nama);
	}
	else if(startnode==2){
		strcpy(namast,st[2].nama);
	}
	else if(startnode==3){
		strcpy(namast,st[3].nama);
	}
	else if(startnode==4){
		strcpy(namast,st[4].nama);
	}
	else if(startnode==5){
		strcpy(namast,st[5].nama);
	}
	else if(startnode==6){
		strcpy(namast,st[6].nama);
	}
	else if(startnode==7){
		strcpy(namast,st[7].nama);
	}
	else if(startnode==8){
		strcpy(namast,st[8].nama);
	}
	else if(startnode==9){
		strcpy(namast,st[9].nama);
	}
	else if(startnode==10){
		strcpy(namast,st[10].nama);
	}
	
	//tujuan
	if(endnode==0){
		strcpy(namast2,st[0].nama);
	}
	else if(endnode==1){
		strcpy(namast2,st[1].nama);
	}
	else if(endnode==2){
		strcpy(namast2,st[2].nama);
	}
	else if(endnode==3){
		strcpy(namast2,st[3].nama);
	}
	else if(endnode==4){
		strcpy(namast2,st[4].nama);
	}
	else if(endnode==5){
		strcpy(namast2,st[5].nama);
	}
	else if(endnode==6){
		strcpy(namast2,st[6].nama);
	}
	else if(endnode==7){
		strcpy(namast2,st[7].nama);
	}
	else if(endnode==8){
		strcpy(namast2,st[8].nama);
	}
	else if(endnode==9){
		strcpy(namast2,st[9].nama);
	}
	else if(endnode==10){
		strcpy(namast2,st[10].nama);
	}
	
	for (x = 0; x < vertex; x++){
		for (y = 0; y < vertex; y++){
			if (adjacency[x][y] == 0){
				temp[x][y] = 9999;
			}
			else{
				temp[x][y] = adjacency[x][y];
			}
		}
	}
	for (x = 0; x < vertex; x++){
		jarak[x] = temp[startnode][x];
		pred[x] = startnode;
		visited[x] = 0;
	}
	jarak[startnode] = 0;
	visited[startnode] = 1;
	count = 1;
	while (count<vertex-1){
		jarakmin = 9999;
		for (x = 0; x < vertex; x++){
			if (jarak[x] < jarakmin && !visited[x]){
				jarakmin = jarak[x];
				nextnode = x;
			}
		}
		visited[nextnode] = 1;
		for (x = 0; x < vertex; x++){
			if (!visited[x]){
				if (jarakmin + temp[nextnode][x] < jarak[x]){
					jarak[x] = jarakmin + temp[nextnode][x];
					pred[x] = nextnode;
				}
			}
		}
		count++;
	}
	
		for (x = 0; x <= endnode; x++){
		  if (x == endnode){
		   printf("\n\n===========================================================");
		   printf("\nstasiun pemberangkatan = %s",namast);
		   printf("\nstasiun tujuan         = %s",namast2);
		   printf("\n\nRute Stasiun = (%s)", st[x].nama);
		   y = x;
		   
		   do{
		    y = pred[y];
		    printf(" <- (%s)", st[y].nama);
		   }
		   while(y != startnode);
		   printf("\n\nJarak dari stasiun %s ke stasiun %s       = %dkm",namast, namast2, jarak[x]);
		   printf("\nHarga tiket dari stasiun %s ke stasiun %s = Rp. %d",namast, namast2, 500 * jarak[x] );
		   printf("\n===========================================================\n\n");
		
		  	}
		 }
}

int main(){
	int pilih;
	int berangkat;
	int tujuan;
	int idval;
	char user[100];
	int height=0;
	struct node *root = 0;
	int vertex = 11;
	int adjacency[11][11]={ {0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
							{5, 0, 20, 0, 0, 0, 0, 0, 0, 10, 0}, 
							{0, 20, 0, 13, 0, 0, 0, 0, 0, 0, 0}, 
							{0, 0, 13, 0, 13, 0, 0, 0, 0, 0, 0}, 
							{0, 0, 0, 13, 0, 5, 20, 0, 0, 0, 0}, 
							{0, 0, 0, 0, 5, 0, 15, 0, 0, 0, 20}, 
							{0, 0, 0, 0, 20, 15, 0, 10, 0, 0, 0}, 
							{0, 0, 0, 0, 0, 0, 10, 0, 15, 0, 0}, 
							{0, 0, 0, 0, 0, 0, 0, 15, 0, 20, 0}, 
							{0, 10, 0, 0, 0, 0, 0, 0, 20, 0, 15}, 
							{0, 0, 0, 0, 0, 20, 0, 0, 0, 15, 0} };
	while (pilih!=6){
		printf("======Station Finder======\n\n");
		printf("-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
		printf("Stasiun: \n");
		printf("0.Utta station\n");
		printf("1.Etogawa station\n");
		printf("2.Shiojiri station\n");
		printf("3.Otsuki station\n");
		printf("4.Chiba station\n");
		printf("5.Ueno station\n");
		printf("6.Shinagawa station\n");
		printf("7.Harajuku station\n");
		printf("8.Meguro station\n");
		printf("9.Shinjiku station\n");
		printf("10.Nikko station\n\n");
		printf("Order: \n");
		printf("1. Cari rute stasiun\n");
		printf("2. Membeli tiket\n");
		printf("3. Tampilkan Data\n");
		printf("4. Hapus Data\n");
		printf("5. Bayar Tiket\n");
		printf("6. Keluar\n");
		printf("Your input: ");
		scanf("%d",&pilih);
		
		if(pilih==1){
			while(1){
			printf(">> Pilih statiun pemberangkatan [0...10]: ");
			scanf("%d",&berangkat);//startnode
			if (berangkat<0 || berangkat>10) {
				printf("\n---Station Doesnt Exist---\n\n");	
								}	
			
			else{
			printf(">> Pilih stasiun tujuan         [0...10]: ");
			scanf("%d",&tujuan);
			if (tujuan<0 || tujuan>10) {
				printf("\n---Station Doesnt Exist---\n\n");	
			}
			else{
			pathfinder(adjacency, vertex, berangkat, tujuan);
			}		
			break;
			}
			}
		} 
		
		else if(pilih==2){
			while(1){ //jika inputan benar
				printf("Input ID St[1-9][0-9]            : St ");
				scanf("%d",&idval);
				if (idval<10 || idval>99){
	        		printf("\n---Id Value too much---\n\n");
	       		} 
	       		else{
	       			while(1){
	       				printf("Input Nama Pelanggan [1...50]    : ");
				        getchar();
				        scanf(" %[^\n]",user);
						if (strlen(user)<0 || strlen(user)>50){
				        	printf("\n---Name Value too much---\n\n");
						}
						else{
							while(1){
								printf(">> Pilih stasiun pemberangkatan [0...10]: ");
								scanf("%d",&berangkat);//startnode
								if (berangkat<0 || berangkat>10) {
									printf("\n---Station Doesnt Exist---\n\n");	
								}	
								else{
									while(1){
										printf(">> Pilih stasiun tujuan         [0...10]: ");
										scanf("%d",&tujuan);
										if (tujuan<0 || tujuan>10) {
											printf("\n---Station Doesnt Exist---\n\n");	
										}	
										else if(search(root,idval)==0){
											root = adddata(root, idval, user, berangkat, tujuan, height);
											break;
										}
										else if(search(root,idval)!=0){
											printf("\n---Add New Data Failed Please Try again\n\n");
											break;
										}
									}
									break;
								}
								
							}
							break;
						}
					}
					break;
				}	
			}
		} 
		else if(pilih==3){
			display(root);
		}
		else if(pilih==4){
			if (root == NULL) {
        		printf("\n--- There is no data in the node ---\n\n");
      		} 
			else {
        		while (1) {
		          printf("Input member ID St[1-9][0-9]: St");
		          scanf("%d", & idval);
		          printf("\n");
				  if (idval < 10 || idval > 99){
				  		printf("-- ID doesn't exist ---\n\n");
				  }
				  else if (search(root, idval) == NULL){
				  		printf("--- Member ID is not found---\n\n");
				  }
				  else if (search(root, idval) != NULL) {
				  		root = delete_data(root, idval);
				  		break;
				  }
				}
            	
          	}
        }
        else if(pilih==5){
			if (root == NULL) {
        		printf("\n--- There is no data in the node ---\n\n");
      		} 
			else {
        		while (1) {
		          printf("Input member ID St[1-9][0-9]: St");
		          scanf("%d", & idval);
		          printf("\n");
				  if (idval < 10 || idval > 99){
				  		printf("-- ID doesn't exist ---\n\n");
				  }
				  else if (search(root, idval) == NULL){
				  		printf("--- Member ID is not found---\n\n");
				  }
				  else if (search(root, idval) != NULL) {
				  		root = buy(root, idval);
				  		break;
				  }
				}
          	}
        }   
    }
	
}

