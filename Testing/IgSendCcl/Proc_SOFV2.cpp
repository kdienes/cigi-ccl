// Proc_SOFV2.cpp: implementation of the Proc_EntityCtrlV3 Parsing
//   Processor class..
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"


#ifndef _WIN32
   #include <fstream>
#elif _MSC_VER > 1300
   #include <fstream>
#else
   #include <fstream.h>
#endif


#include "Proc_SOFV2.h"
#include "ParseValue.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Proc_SOFV2::Proc_SOFV2()
{
   PcktID = "SOFV2";
}

Proc_SOFV2::~Proc_SOFV2()
{

}


void Proc_SOFV2::ProcPckt(ParseValue *pPV)
{

   if(Omsg == NULL)
      return;


   printf("Start Of Frame V2:\n");
   pPV = pPV->nxt();  // skip the cmd name

   if(pPV != NULL)
   {
      try
      {
         Om_SOFV2.SetDatabaseID(pPV->GetChar(),true);
         printf("\tDatabase ID = %d\n",pPV->GetChar());
      }
      catch(CigiValueOutOfRangeException ORX)
      {
         if(ORX.HasMessage())
            printf("%s\n",ORX.what());
      }

      pPV = pPV->nxt();
   }

   if(pPV != NULL)
   {
      try
      {
         Om_SOFV2.SetIGStatus(pPV->GetUChar(),true);
         printf("\tIG Status = %u\n",pPV->GetUChar());
      }
      catch(CigiValueOutOfRangeException ORX)
      {
         if(ORX.HasMessage())
            printf("%s\n",ORX.what());
      }

      pPV = pPV->nxt();
   }

   if(pPV != NULL)
   {
      try
      {
         if(strcmp("Reset",pPV->GetStr()) == 0)
         {
            Om_SOFV2.SetIGMode(CigiBaseSOF::Reset,true);
            printf("\tIG Mode = 0 : Reset\n");
         }
         else if(strcmp("Operate",pPV->GetStr()) == 0)
         {
            Om_SOFV2.SetIGMode(CigiBaseSOF::Operate,true);
            printf("\tIG Mode = 1 : Operate\n");
         }
         else if(strcmp("debug",pPV->GetStr()) == 0)
         {
            Om_SOFV2.SetIGMode(CigiBaseSOF::debug,true);
            printf("\tIG Mode = 2 : debug\n");
         }
         else if(strcmp("OfflineMaint",pPV->GetStr()) == 0)
         {
            Om_SOFV2.SetIGMode(CigiBaseSOF::OfflineMaint,true);
            printf("\tIG Mode = 3 : OfflineMaint\n");
         }
      }
      catch(CigiValueOutOfRangeException ORX)
      {
         if(ORX.HasMessage())
            printf("%s\n",ORX.what());
      }

      pPV = pPV->nxt();
   }

   if(pPV != NULL)
   {
      try
      {
         Om_SOFV2.SetFrameCntr(pPV->GetULong(),true);
         printf("\tFrame Counter = %u\n",pPV->GetULong());
      }
      catch(CigiValueOutOfRangeException ORX)
      {
         if(ORX.HasMessage())
            printf("%s\n",ORX.what());
      }

      pPV = pPV->nxt();
   }

   if(pPV != NULL)
   {
      try
      {
         Om_SOFV2.SetTimeStamp(pPV->Getfloat(),true);
         printf("\tTime Stamp = %f\n",pPV->Getfloat());
      }
      catch(CigiValueOutOfRangeException ORX)
      {
         if(ORX.HasMessage())
            printf("%s\n",ORX.what());
      }

      pPV = pPV->nxt();
   }

   *Omsg << Om_SOFV2;


}


