for m in range(50,100): #m為結點數
    b = [] #用list b來儲存點與邊，ex [2,5,10]表node2與node5間有長度=10的道路
    for i in range(0,m):
        for j in range(0,m):
            if(i>j): #假設實驗是無向圖，故只考慮i>j情況
                a = random.randint(0,100) 
                if(i!=j):
                    if(abs(i-j) < round(((0.05)*m))): 
                    # 如果i與j的差距小，則有20%的機率生成長度1~100的edge
                        if(a<=20):
                            x = random.randint(1,100)
                            b.append([i,j,x])
                    elif(abs(i-j)<(round((0.3)*m))):
                    # 如果i與j的差距適中，則有10%的機率生成長度100~500的edge
                        if(a<=10):
                            x = random.randint(100,500)
                            b.append([i,j,x])
                    # 如果i與j的差距大，則有5%的機率生成長度500~1000的edge
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
    
    #繪圖部分
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