import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as mp



def main():
    resultsDF,denseResultsDF,K3ResultsDF,K4ResultsDF,flowResultsDF,relaxResultsDF = getResults()
    drawValueByArcs(resultsDF,denseResultsDF,K3ResultsDF,K4ResultsDF,flowResultsDF,relaxResultsDF)
    drawTimeByArcs(resultsDF,denseResultsDF,K3ResultsDF,K4ResultsDF,flowResultsDF,relaxResultsDF)



def drawTimeByArcs(resultsDF,denseResultsDF,K3ResultsDF,K4ResultsDF,flowResultsDF,relaxResultsDF):
    def takeSecond(elem):
        return elem[1]
    global edmondsResults
    edmondsResults.sort(key=takeSecond)
    edmondsResultsDF = pd.DataFrame(edmondsResults,columns=["Nb sommets","Nb arcs","Valeur edmonds","Temps edmonds"])

    denseResultsDF = denseResultsDF.sort_values("Nb arcs")
    K3ResultsDF = K3ResultsDF.sort_values("Nb arcs")
    K4ResultsDF = K4ResultsDF.sort_values("Nb arcs")
    flowResultsDF = flowResultsDF.sort_values("Nb arcs")
    relaxResultsDF = relaxResultsDF.sort_values("Nb arcs")

    edmondStop = 12
    X1 = edmondsResultsDF["Nb arcs"][0:edmondStop]
    X2 = denseResultsDF["Nb arcs"]
    X3 = K3ResultsDF["Nb arcs"]
    X4 = K4ResultsDF["Nb arcs"]
    X5 = relaxResultsDF["Nb arcs"]
    X6 = flowResultsDF["Nb arcs"][0:128]
    Xs = [X1,X2,X3,X4,X5,X6]

    Y1 = edmondsResultsDF["Temps edmonds"][0:edmondStop]
    Y2 = denseResultsDF["Temps matching PLNE"]
    Y3 = K3ResultsDF["Temps PLNE K=3"]
    Y4 = K4ResultsDF["Temps PLNE K=4"]
    Y5 = relaxResultsDF["Temps relax PLNE"]
    Y6 = flowResultsDF["Temps flot"][0:128]
    Ys = [Y1,Y2,Y3,Y4,Y5,Y6]

    colors = [(1,0.0,0.0),(247/255, 95/255, 25/255),(0.4,0.85,0.0),(9/255, 212/255, 235/255),(92/255, 9/255, 235/255),(240/255, 34/255, 161/255)]
    labelsNames = ["K=2 edmonds","K=2 PLNE","K=3","K=4","relaxation PLNE","relaxation flot"]

    fig, ax = mp.subplots(figsize =(12, 6))
    for index in range(6):
        fit = np.polyfit(Xs[index],Ys[index],1)
        fit_fn = np.poly1d(fit)
        ax.plot(Xs[index],fit_fn(Xs[index]),color=colors[index])

    ax.loglog()
    mp.legend(labels=labelsNames)
    ax.set_ylabel("Temps de résolution en secondes")
    ax.set_xlabel("Nombre de greffes réalisables")
    #mp.title("")
    mp.show()


def drawValueByArcs(resultsDF,denseResultsDF,K3ResultsDF,K4ResultsDF,flowResultsDF,relaxResultsDF):
    denseResultsDF = denseResultsDF.sort_values("Nb arcs")
    matchStop = 54
    X1 = denseResultsDF["Nb arcs"][0:matchStop]
    X2 = denseResultsDF["Nb arcs"]
    Xs = [X1,X2,X2,X2]

    Y1 = denseResultsDF["Valeur matching"][0:matchStop]
    Y2 = denseResultsDF["Valeur PLNE K=3"]
    Y3 = denseResultsDF["Valeur PLNE K=4"]
    Y4 = denseResultsDF["Valeur relax"]

    Ys = [Y1,Y2,Y3,Y4]
    colors = [(1,0.0,0.0),(0.4,0.85,0.0),(9/255, 212/255, 235/255),(92/255, 9/255, 235/255)]
    labelsNames = ["K=2","regression K=2","K=3","regression K=3","K=4","regression K=4","relaxation","regression relaxation"]

    fig, ax = mp.subplots(figsize =(12, 6))
    for index in range(4):
        fit = np.polyfit(Xs[index],Ys[index],2)
        fit_fn = np.poly1d(fit)
        ax.plot(Xs[index],Ys[index],color=toGray(colors[index]))
        ax.plot(Xs[index],fit_fn(Xs[index]),color=colors[index])

    mp.legend(labels=labelsNames)
    ax.set_ylabel("Nombre de greffes choisies de l'optimum")
    ax.set_xlabel("Nombre de greffes réalisables")
    #mp.title("")
    mp.show()



def toGray(color,increase=0.25):
    newColor = [None,None,None]
    lumos = (color[0]+color[1]+color[2])/3
    newColor[0] = min(((color[0]+lumos)/2)+increase,1)
    newColor[1] = min(((color[1]+lumos)/2)+increase,1)
    newColor[2] = min(((color[2]+lumos)/2)+increase,1)
    return newColor



def getResults():
    print(getTest("../../solutions/lip/4/00036-00000028.wmd.sol"))
    fileNames = next(os.walk("../../data/kidney"), (None, None, []))[2] #one-liner qui donne la liste des fichiers dans un répertoire

    results = []
    denseResults = []
    K3Results = []
    K4Results = []
    flowResults = []
    relaxResults = []
    for fileName in fileNames:
        matching_fileExists,matching_nbCouples,matching_nbTransplants,matching_value,matching_time = getTest("../../solutions/lip/2/"+fileName+".sol")
        K3_fileExists,K3_nbCouples,K3_nbTransplants,K3_value,K3_time = getTest("../../solutions/lip/3/"+fileName+".sol")
        K4_fileExists,K4_nbCouples,K4_nbTransplants,K4_value,K4_time = getTest("../../solutions/lip/4/"+fileName+".sol")
        relax_fileExists,relax_nbCouples,relax_nbTransplants,relax_value,relax_time = getTest("../../solutions/lip/relax/"+fileName+".sol")
        flow_fileExists,flow_nbCouples,flow_nbTransplants,flow_value,flow_time = getTest("../../solutions/flow/"+fileName+".sol")

        result = [fileName,relax_nbCouples,relax_nbTransplants,relax_value,flow_time,relax_time,matching_value,matching_time,K3_value,K3_time,K4_value,K4_time]

        if(matching_fileExists or K3_fileExists or K4_fileExists or relax_fileExists or flow_fileExists):
            results += [result]

        if(matching_fileExists and K3_fileExists and K4_fileExists and relax_fileExists and flow_fileExists):
            denseResults += [result]

        if K3_fileExists:
            K3Results += [result]
        if K4_fileExists:
            K4Results += [result]
        if flow_fileExists:
            flowResults += [result]
        if relax_fileExists:
            relaxResults += [result]

    columnsNames = ["Nom","Nb sommets","Nb arcs","Valeur relax","Temps flot","Temps relax PLNE","Valeur matching","Temps matching PLNE","Valeur PLNE K=3","Temps PLNE K=3","Valeur PLNE K=4","Temps PLNE K=4"]

    resultsDF = pd.DataFrame(results,columns=columnsNames)
    denseResultsDF = pd.DataFrame(denseResults,columns=columnsNames)
    K3ResultsDF = pd.DataFrame(K3Results,columns=columnsNames)
    K4ResultsDF = pd.DataFrame(K4Results,columns=columnsNames)
    flowResultsDF = pd.DataFrame(flowResults,columns=columnsNames)
    relaxResultsDF = pd.DataFrame(relaxResults,columns=columnsNames)

    print(resultsDF)
    resultsDF.to_csv("results.csv", sep=';')
    return resultsDF,denseResultsDF,K3ResultsDF,K4ResultsDF,flowResultsDF,relaxResultsDF



def getTest(filePath):
    try:
        file = open(filePath,"r")
        lines = file.readlines()
        file.close()
        fileExists = True
        nbCouples = int(lines[5])
        nbTransplants = int(lines[7])
        value = int(lines[11])
        time = int(lines[13])
    except:
        fileExists = False
        nbCouples = None
        nbTransplants = None
        value = None
        time = None

    return fileExists,nbCouples,nbTransplants,value,time



edmondsResults = [
[16,59,2*2,156/1000],
[16,70,1*2,180/1000],
[18,96,5*2,328/1000],
[32,268,8*2,445/1000],
[32,168,2*2,157/1000],
[35,370,8*2,636/1000],
[64,1087,18*2,961/1000],
[64,961,13*2,654/1000],
[70,1597,22*2,1522/1000],
[128,3704,31*2,2028/1000],
[128,4206,35*2,2173/1000],
[140,6382,46*2,4139/1000],
[256,15569,67*2,4513/1000],
[512,67589,152*2,15428/1000],
[1024,267471,321*2,68231/1000],
[2048,1002827,598*2,272642/1000],]



main()
