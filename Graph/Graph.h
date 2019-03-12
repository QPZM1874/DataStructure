//***********   Graph.h   ************//
//ͼ�Ļ���
#ifndef GRAPH_H
#define GRAPH_H

#define UNVISITED 0
#define VISITED 1


#define INFINITE 0x0fffffff // ��ʾ�����
// �����·��ʱ�������ͱȽ�INFINITE+INFINITE��INFINITE+weight��
// ��˲��ܶ���Ϊ���͵����ֵ��4�ֽ�int���ֵΪ0x7ffffffff

//Edge��
class Edge
{
public:
    int weight;    //weight�Ǳߵ�Ȩ
    int from;      //from�Ǳߵ�ʼ��
    int to;        //to�Ǳߵ��յ�
    Edge()   	   // ���캯��
    {
        from = -1;
        to = -1;
        weight = 0;
    }
    Edge(int f,int t,int w)     // ���캯��
    {
        from=f;
        to=t;
        weight=w;
    }
    bool operator < (const Edge &arg)
    {
        return (this->weight < arg.weight);
    };
    bool operator == (const Edge &arg)
    {
        return (this->weight == arg.weight);
    };
    bool operator > (const Edge &arg)
    {
        return (this->weight > arg.weight);
    };
    bool operator <= (const Edge &arg)
    {
        return (this->weight <= arg.weight);
    };
    bool operator >= (const Edge &arg)
    {
        return (this->weight >= arg.weight);
    };
};

// ͼ���ࡣ
// �����࣬����ʵ���������н���������ʵ���й������ԣ�
// û�о���Ľ���ϵʵ��
class Graph
{
public:
    int numVertex;             //ͼ�Ķ���ĸ���
    int numEdge;				//ͼ�ıߵ���Ŀ
    int *Mark;					/*Markָ��ָ�򱣴���ͼ�Ķ���ı�־λ������,��־λ�������ĳ�����Ƿ񱻷��ʹ�*/
    int *Indegree;				//Indegreeָ��ָ�򱣴���ͼ�Ķ������ȵ�����
    Graph(int numVert)   		//���캯��
    {
        numVertex = numVert;      //ȷ��ͼ�Ķ���ĸ���
        numEdge = 0;				//ȷ��ͼ�ıߵ���Ŀ
        Indegree = new int[numVertex]; /*Ϊ����ͼ�Ķ���������������,IndegreeΪ����ָ��*/
        Mark = new int[numVertex];	 /*Ϊͼ�Ķ���ı�־λ��������,MarkΪ����ָ��*/

        for (int i = 0; i < numVertex; i ++)   	/*ȷ��ͼ�Ķ���ı�־λ�����,�����ж���ı�־λ��ʼ��Ϊδ�����ʹ�,��ȳ�ʼ��Ϊ0*/
        {
            Mark[i] = UNVISITED;
            Indegree[i] = 0;
        }
    }

    ~Graph()  				//��������
    {
        delete [] Mark;
        delete [] Indegree;
    }

    virtual Edge FirstEdge(int oneVertex)  	// �����붥��oneVertex������ĵ�һ����
    {
        Edge myEdge;
        myEdge.from = oneVertex;
        myEdge.to = -1;   ///��ʵ�ϲ���һ��ʵ�ʵıߣ���������࣬��ʵ������
        return myEdge;
    }

    virtual Edge NextEdge(Edge preEdge)    // �������PreEdge����ͬ�����������һ����
    {
        return preEdge;
    }

    int VerticesNum()  		//����ͼ�Ķ������
    {
        return numVertex;
    }

    int EdgesNum()  			//����ͼ�ı���
    {
        return numEdge;
    }

    int FromVertex(Edge oneEdge)    // ����oneEdge��ʼ��
    {
        return oneEdge.from;
    }

    int ToVertex(Edge oneEdge)  	// ����oneEdge���յ�
    {
        return oneEdge.to;
    }

    int Weight(Edge oneEdge)  		// ����oneEdge��Ȩֵ
    {
        return oneEdge.weight;
    }

    bool IsEdge(Edge oneEdge)   //���oneEdge�Ǳ��򷵻�TRUE�����򷵻�FALSE
    {
        if (oneEdge.weight > 0 && oneEdge.weight < INFINITE && oneEdge.to >= 0)
            return true;
        else
            return false;
    }

    bool IsEdgeForShortestPath(Edge oneEdge)   	//���oneEdge�Ǳ��򷵻�TRUE�����򷵻�FALSE
    {
        // ר��Ϊ���·���㷨��ƣ���"�����Ȩ��"��Ϊ�ߡ�
        // ��ȨΪ"�����"Ҳ�����Ǳߣ�����Dijkstra��Floyd�㷨�У�
        // ��ѭ������һ������������ڽӵ�ʱ���洢˳���м���ַ�
        // �ڽӵ�ʱ��ѭ����ֹ�����º�����ڽӵ㲻������
        if (oneEdge.weight > 0 && oneEdge.weight <= INFINITE && oneEdge.to >= 0)
            return true;
        else
            return false;
    }

    virtual void setEdge(int from, int to, int weight) = 0;
    virtual void delEdge(int from, int to) = 0;
};

#endif // GRAPH_H
