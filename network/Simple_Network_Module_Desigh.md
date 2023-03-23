# DS_HW4
#107304053統計四 吳苡菡

1.	設計公路網路模型（30%）
我的方法：
input 為 node 數，假設 node 數為 100 ，則建立 node 0，node 1，....，node 99，
其中用兩個 node 之間的差距來決定兩個 node之間是否有 edge，例如 node 1 和 node 2之間的差距是 (2-1)=1，那麼它們之間會有較高的機率有邊相連，但相連的edge的長度會較短，而若是 node 1與 node 99，它們之間會有較小的機率有邊相連，但若有邊，邊的距離會較長，如此在任兩個 node之間都判斷一次是否有邊相連，以建成一個公路模型，以下為 n=100 時所生出的 graph，可以看到圖中央的點的edge會比較密集，而外圍的點的edge會比較稀疏，以公路圖的概念來說，可以把圖中央想像成市中心，周圍想像成外圍鄉鎮。

![](https://i.imgur.com/9l7hQWQ.jpg)
![](https://i.imgur.com/lbyX5WB.jpg)
![](https://i.imgur.com/5RK8J0O.jpg)
![](https://i.imgur.com/UnSihEz.jpg)
![](https://i.imgur.com/yGRRfWu.jpg)

3.	撰寫程式探討節點數對於平均距離的影響（20%）
	平均距離＝(∑_(任兩相異節點v_i,v_j)/[v_i 與v_j 的最短距離])/(C_2^n )
    這邊因為 dijkstra演算法是處理single source時較方便的演算法，但不太適合求這種每個點之間的最小距離，故我採用 FloydWarshall演算法去求各點間的最短距離，並取平均後繪製成折線圖。
    y軸為距離，x軸為node數
    ![](https://i.imgur.com/gsWSIy0.png)
    可以觀察到，當結點數越來越多，平均距離會有越來越短的趨勢，這是因為每當結點增加，依照我的公路模型生成的條件，到另一個點有更短路線的機率也會跟著增加，ex：如果原本只有 node 0~9，當多了一個點(node 10)時，每個點都有機會因為多了這個 node 10 使得任兩點間的路徑更短(因為有可能node[w]<node[10]+node[10,w])
    
    故在理想狀態下，當結點數越來越多，平均距離應該會越來越短，而平均距離減少的比例則與公路模型的條件有較大的關係。


5.	比較不同heap對於 Dijkstra 演算法執行時間的影響（50%）
    為了方便看出實驗結果，我在設計公路模型時有刻意讓圖中的edge數不要太多，如此一來使用heap與array的時間差距會更明顯

    理論來說，如果用 array 實作 Dijkstra，時間複雜度會是 O(V^2)，而若是使用 heap 實作 Dijkstra，時間複雜度會落在 O(ElogV)，我的實驗得到的結果如圖，y軸為時間，x軸為2的次方數，
    
    這次使用的語言是 python，因為用 networkx 以及 matplotlib 繪圖十分方便，但是經過眾多嘗試還是無法把次方數再往上提高，所以好像沒有辦法很完美的看出使用heap時的時間複雜度是否真的是 O(ElogV)
    
    但對於這兩中資料結構所實行的 Dijkstra 演算法，在不同 case 會有不同的優缺點，也就是說，如果這個圖是 sparse graph，那麼使用 heap 的時間會比較理想，但以極端情況來說，如果圖是一個 Complete graph (i.e 邊很多)，那麼使用 array 會是比較好的選擇。
    
![](https://i.imgur.com/eksQlrV.png)







* code
```
for m in range(50,100): //m為結點數
    b = [] //用list b來儲存點與邊，ex [2,5,10]表node2與node5間有長度=10的道路
    for i in range(0,m):
        for j in range(0,m):
            if(i>j): //假設實驗是無向圖，故只考慮i>j情況
                a = random.randint(0,100) 
                if(i!=j):
                    if(abs(i-j) < round(((0.05)*m))): 
                    // 如果i與j的差距小，則有20%的機率生成長度1~100的edge
                        if(a<=20):
                            x = random.randint(1,100)
                            b.append([i,j,x])
                    elif(abs(i-j)<(round((0.3)*m))):
                    // 如果i與j的差距適中，則有10%的機率生成長度100~500的edge
                        if(a<=10):
                            x = random.randint(100,500)
                            b.append([i,j,x])
                    // 如果i與j的差距大，則有5%的機率生成長度500~1000的edge
                    else:
                        if(a<=5):
                            x = random.randint(500,1000)
                            b.append([i,j,x])
    
    t = time.process_time()
     
    graph = initial_graph(m, b)
    spst = dijkstra(graph, graph[0])
    
    t = time.process_time() - t
    timee.append(t)
    
    graph = initial_graph(m, b)
    adj_M = to_adj_matrix(graph)
    floyd(adj_M)
    sum = 0
    for i in range(0,m):
        for j in range(0,m):
            if(i>j):
                sum = sum + adj_M[i][j]
    from scipy.special import comb, perm //算平均距離
    a = sum/comb(m,2)
    print(a)
    
    //繪圖部分
    import networkx as nx 
    import matplotlib.pyplot as plt 
    
    fig = plt.figure(figsize=(40, 40)) 
    G = nx.fast_gnp_random_graph(300, 0.02, seed=1337) 
    nx.draw(graph, node_size=30) 
    plt.axis('equal') 
    plt.show() 
    fig.savefig('waka.svg')

    x = np.arange(7, 15)
    y = np.array(timee)
    t = np.array(time)
    plt.title("Line graph")
    plt.xlabel("X axis")
    plt.ylabel("Y axis")
    plt.plot(x, y, color ="green")
    plt.plot(x, t, color ="blue")
    plt.show()    
```