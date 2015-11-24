#!/bin/bash

sampleList_in_ALL="data_double_eg_2015D_promptRecoV4_25ns,data_double_mu_2015D_promptRecoV4_25ns,data_muon_eg_2015D_promptRecoV4_25ns,data_single_electron_2015D_promptRecoV4_25ns,data_single_muon_2015D_promptRecoV4_25ns,data_met_2015D_promptRecoV4_25ns,data_muon_eg_2015D_05Oct2015_v2_25ns,data_double_eg_2015D_05Oct2015_v1_25ns,data_double_mu_2015D_05Oct2015_v1_25ns,data_muon_eg_2015D_05Oct2015_v1_25ns,data_single_electron_2015D_05Oct2015_v1_25ns,data_single_muon_2015D_05Oct2015_v1_25ns,data_met_2015D_05Oct2015_v1_25ns,data_double_eg_2015D_promptRecoV3_25ns,data_double_mu_2015D_promptRecoV3_25ns,data_muon_eg_2015D_promptRecoV3_25ns,data_single_electron_2015D_promptRecoV3_25ns,data_single_muon_2015D_promptRecoV3_25ns,data_met_2015D_promptRecoV3_25ns,data_double_eg_2015C_25ns,data_double_mu_2015C_25ns,data_muon_eg_2015C_25ns,data_single_electron_2015C_25ns,data_single_muon_2015C_25ns,data_met_2015C_25ns,ttbar_madgraph_pythia8_25ns,ttbar_singleLeptFromT_madgraph_pythia8_25ns,ttbar_singleLeptFromT_madgraph_pythia8_ext1_25ns,ttbar_singleLeptFromTbar_madgraph_pythia8_25ns,ttbar_singleLeptFromTbar_madgraph_pythia8_ext1_25ns,ttbar_diLept_madgraph_pythia8_25ns,ttbar_diLept_madgraph_pythia8_ext1_25ns,ttbar_powheg_pythia8_25ns,ttbar_powheg_pythia8_ext3_25ns,ttbarTo2L2Nu_powheg_25ns,tbar_tch_4f_powheg_pythia8_25ns,t_tch_4f_powheg_pythia8_25ns,t_sch_4f_amcnlo_pythia8_25ns,t_tbarW_5f_powheg_pythia8_25ns,t_tW_5f_powheg_pythia8_25ns,DYJetsToLL_m10To50_amcnlo_pythia8_25ns,DYJetsToLL_m50_amcnlo_pythia8_25ns,WJetsToLNu_madgraph_pythia8_25ns,WJetsToLNu_HT100To200_madgraph_pythia8_25ns,WJetsToLNu_HT200To400_madgraph_pythia8_25ns,WJetsToLNu_HT400To600_madgraph_pythia8_25ns,WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns,WJetsToLNu_HT600To800_madgraph_pythia8_25ns,WJetsToLNu_HT800To1200_madgraph_pythia8_25ns,WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns,WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns,WW_pythia8_25ns,WWToLNuQQ_powheg_25ns,WWToLNuQQ_amcnlo_pythia8_25ns,WWTo2l2Nu_powheg_25ns,WZ_pythia8_25ns,WZ_amcnlo_pythia8_25ns,WZTo3LNu_powheg_pythia8_25ns,WZTo2L2Q_amcnlo_pythia8_25ns,WZTo1L3Nu_amcnlo_pythia8_25ns,WZTo1LNu2Q_amcnlo_pythia8_25ns,ZZ_pythia8_25ns,ZZTo2L2Q_amcnlo_pythia8_25ns,ZZTo2L2Nu_powheg_pythia8_25ns,ZZTo2Q2Nu_amcnlo_pythia8_25ns,ZZTo4L_powheg_pythia8_25ns,TTWJetsToQQ_amcnlo_pythia8_25ns,TTWJetsToLNu_amcnlo_pythia8_25ns,TTZToQQ_amcnlo_pythia8_25ns,TTZToLLNuNu_M-10_amcnlo_pythia8_25ns,TTGJets_amcnlo_pythia8_25ns,tZq_ll_4f_amcnlo_pythia8_25ns,tZq_nunu_4f_amcnlo_pythia8_25ns,tGJets_amcnlo_pythia8_25ns,T2tt_2J_mStop_425_mLSP_325_25ns,T2tt_2J_mStop_500_mLSP_325_25ns,T2tt_2J_mStop_650_mLSP_325_25ns,T2tt_2J_mStop_850_mLSP_100_25ns,T6bbWW_mStop425_mCh400_mLSP50"

sampleList_ALL=`echo $sampleList_in_ALL | tr ',' ' ' `


#Choose the sample(s) you want here,separated by commmas

## Custom ##
sampleList_in="ttbar_singleLeptFromT_madgraph_pythia8_ext1_25ns,ttbar_singleLeptFromTbar_madgraph_pythia8_ext1_25ns,ttbar_diLept_madgraph_pythia8_ext1_25ns,ttbar_powheg_pythia8_ext3_25ns"

## ALL ##
#sampleList_in="ALL"


#Choose the number of events (per file): 
nEvents=-1

#Decide if you want lots of printouts telling you the status
verbose="false"

#Set directory to copy results to when finished
copy_dir=/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__bTagEfficiency_v1__20151123/
if [ ! -d $copy_dir/merged_files ]; then
    mkdir $copy_dir/merged_files
fi

#Check that log file folder and tarball files exists
if [ ! -d logs ]; then echo "Run . copy.sh first!"; return 1; fi
if [ ! -e $HOME/$CONDOR_DIR_NAME.tar.gz ]; then echo "Run . copy.sh first!"; return 1; fi


#Set directory with the location of the tarball with code
tar_file=$HOME/$CONDOR_DIR_NAME.tar.gz

#------HERE THERE BE DRAGONS---------

#Parse sampleList
sampleList=`echo $sampleList_in | tr ',' ' ' `
nSamples=`echo "$sampleList" | wc -w`
echo "$sampleList" | grep "ALL" &>/dev/null
isAll="$?" #note this is opposite
if [ "$isAll" == "0" ] && [ "$nSamples" -gt "1" ]; then echo "Aborting! You can't have ALL as well as other sampleLists, dumbass!"; return 1; fi  
if [ "$isAll" == "0" ]
then 
  sampleList=$sampleList_ALL

  sampleList_in=$sampleList_in_ALL
fi

#nSubmitted (so you know when to quit)
nSubmitted=0

#Start by checking proxy, get path to proxy file
voms-proxy-info --all &> voms_status.txt
if grep "Couldn't find a valid proxy." voms_status.txt &>/dev/null
then 
  echo "Error: couldn't find a valid proxy!  Aborting.  Create a proxy with voms-proxy-init."
  rm voms_status.txt
  return 1
fi
lineWithPath=`sed -n /path/= voms_status.txt`
pathToProxy=`awk -v var="$lineWithPath" 'NR==var {print $3}' voms_status.txt`

#Do all this stuff once per sample
for sample in $sampleList
do
  #echo "Processing $sample"
  
  #Make a list of all the files on hadoop you want to run on
  sample_dir=""

  #number of lines in sample.dat
  nLines=`wc -l < ../sample.dat`

  samplename=""
  sampledir=""

  #loop to find sample_dir
  for (( i = 1; i <= $nLines; i++ ))
  do

    #get string in sample.dat, temptwo is either the samplename or the sampledirectory
    temp=`awk "NR==$i" ../sample.dat`
    tempone=`echo $temp |cut -d' ' -f1`
    temptwo=`echo $temp |cut -d' ' -f2`

    #store the sample name
    if [ "$tempone" == "Name" ]; then
        samplename="$temptwo"
    fi

    #store the sampledir
    if [ "$tempone" == "Path" ]; then
        sampledir="$temptwo"
	#if sampledir is in the list make it sample_dir
        if [ "$sample" == "$samplename" ]; then
           sample_dir="$sampledir"
        fi
    fi
    #sample_dir already found
    if [ "$sample_dir$" == "$sampledir" ]; then
       break
    fi

  done
  
  for file in `/bin/ls $sample_dir/merged_ntuple_*.root`; do

    number_temp=${file##*/merged_ntuple_}
    number=${number_temp%*.root}

    #Except they've finished
    if [ -e $copy_dir/bTagEfficiency__${sample}_${number}.root ] 
    then 
      if [ "$verbose" == "true" ]; then echo "-------------"; echo "${copy_dir}/bTagEfficiency__${sample}_${number} already exists on hadoop, will not resubmit"; fi
      continue
    fi  

    #Status message
    if [ "$verbose" == "true" ]; then echo "-------------"; echo "Working on ${copy_dir}/bTagEfficiency__${sample}_${number}"; fi
    
    #Or if they're still running
    if [ -e logs/condorLog_${sample}_${number}.log ] 
    then
      while read line
      do
        if [ `echo $line | awk '{ print $1 }'` == "Cluster" ] 
        then
          cluster=`echo $line | awk '{ print $3 }'`
        elif [ `echo $line | awk '{ print $1 }'` == "Proc" ] 
        then
          process=`echo $line | awk '{ print $3 }'`
        fi  
      done < logs/condorLog_${sample}_${number}.log
      jobid="$cluster.$process"
      condor_q $jobid > temp.txt
      result=`more temp.txt | awk 'END{print $1}'`
      if [ "$result" == "$jobid" ] 
      then
        if [ "$verbose" == "true" ]; then echo "already submitted!"; fi
        let "nSubmitted=$nSubmitted+1"
        continue
      fi  
    fi  
    if [ "$verbose" == "true" ]; then echo "submitting..."; fi
    let "nSubmitted=$nSubmitted+1"

    #Then submit
    cp condorFileTemplate condorFile
    sed -i "s,ARG1,$sample,g" condorFile
    sed -i "s,ARG2,$nEvents,g" condorFile
    sed -i "s,ARG3,$number,g" condorFile
    sed -i "s,ARG4,$copy_dir,g" condorFile
    sed -i "s,ARG5,$CONDOR_DIR_NAME,g" condorFile
    sed -i "s,ARG6,$MAKER_NAME,g" condorFile
    sed -i "s,USER_PROXY,$pathToProxy,g" condorFile
    sed -i "s,TARFILE,$tar_file,g" condorFile
    condor_submit condorFile
  done
done

#Clean up
rm voms_status.txt &>/dev/null
rm temp.txt &>/dev/null

#Merge
notZombieFile=logs/notZombies.txt
if [ ! -e $notZombieFile ]
then
  echo "" >> $notZombieFile
fi 

nZombies=0
if [ "$nSubmitted" == "0" ] 
then
  #Check for zombies which should be deleted in copy_dir
  echo "CHECKING FOR ZOMBIES"
  for file in `/bin/ls $copy_dir/*.root`
  do
    # Check if file already checked 
    firstCheck=""
    firstCheck=`more $notZombieFile | grep $file`
    if [ -z $firstCheck ]
    then
	root -l -b -q checkForZombies.C'("'$file'","'$notZombieFile'")'
	secondCheck=""
	secondCheck=`more $notZombieFile | grep $file`
	if [ -z $secondCheck ]
	then
	    echo "  FOUND ZOMBIE!"
	    nZombies=$((nZombies+1))
	    echo "  DELETING FILE: $zombie"
	    rm -rf $secondCheck
	    echo "  JOB WILL BE RESUBMITTED"
	fi
    fi
    
  done

  if [ "$nZombies" == "0" ]; then
    . mergeAll.sh $copy_dir $sampleList_in
    sleep 120
    mv *.root $copy_dir/merged_files/
  fi
fi


#Timer
if [ "$verbose" == "true" ]; then 
    echo `date +"%Y%m%d_%H%M%S"`
fi

#Return exit code
if [ "$nSubmitted" == "0" ] && [ "$nZombies" == "0" ]
then 
    return 1
else 
    return 0
fi

