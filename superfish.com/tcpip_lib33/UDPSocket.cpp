/*
 *
 *  Copyright (c) 2000 Barak Weichselbaum <barak@komodia.com>
 *  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 * Contact info:
 * Site: http://www.komodia.com
 * Email: barak@komodia.com
 */

#include "stdafx.h"
#include "UDPSocket.h"

#ifdef _MEMORY_DEBUG 
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif

	KOMODIA_NAMESPACE_START

#define CUDPSocket_Class "CUDPSocket"

CUDPSocket::CUDPSocket() : CSpoofSocket()
{	
	try
	{
		SetName(CUDPSocket_Class);
	}
	ERROR_HANDLER("CUDPSocket")
}

CUDPSocket::~CUDPSocket()
{
}

BOOL CUDPSocket::Create()
{
	try
	{
		SetProtocol(IPPROTO_UDP);
		return CSpoofSocket::Create(IPPROTO_UDP);
	}
	ERROR_HANDLER_RETURN("Create",FALSE)
}

BOOL CUDPSocket::Send(int iSourcePort, 
					  IP aDestinationAddress, 
					  int iDestinationPort,
					  const char* buf,
					  int BufLength)
{
	try
	{
		//Quit if not ok
		if (!CheckSocketValid())
			return FALSE;

		if (isRaw())
		{
			//We can construct the UDP here
			LPUDPHeader lpUDP;
			lpUDP=new UDPHeader;

			//Set the ports
			lpUDP->SourcePort=htons(iSourcePort);
			lpUDP->DestinationPort=htons(iDestinationPort);

			//Set the length
			lpUDP->Length=htons(UDPHeaderLength);

			//Check sum
			lpUDP->Checksum=0;

			BOOL bResult;

			if (BufLength)
			{
				//Create the buffer
				int iTotalLength;
				iTotalLength=UDPHeaderLength+BufLength;

				char* tmpBuf;
				tmpBuf=new char[iTotalLength];

				//Set the length
				lpUDP->Length=htons(iTotalLength);

				memcpy(tmpBuf,lpUDP,UDPHeaderLength);
				memcpy(tmpBuf+UDPHeaderLength,buf,BufLength);
				
				//Update it
				lpUDP->Checksum=CalculatePseudoChecksum(tmpBuf,iTotalLength,aDestinationAddress,iTotalLength);

				//Recopy it
				memcpy(tmpBuf,lpUDP,UDPHeaderLength);

				//Set the new checksum (if applicateable)
				FinalUDPHeader(lpUDP);

				//Send it
				bResult=CSpoofSocket::Send(aDestinationAddress,tmpBuf,iTotalLength,iDestinationPort);

				//Delete
				delete tmpBuf;
			}
			else
			{
				//Update it
				lpUDP->Checksum=CalculatePseudoChecksum((char*)lpUDP,UDPHeaderLength,aDestinationAddress,UDPHeaderLength);

				//Set the new checksum (if applicateable)
				FinalUDPHeader(lpUDP);

				//Send it
				bResult=CSpoofSocket::Send(aDestinationAddress,(char*)lpUDP,UDPHeaderLength,iDestinationPort);
			}

			//Clean up
			delete lpUDP;

			return bResult;
		}
		else
			return CSpoofSocket::Send(aDestinationAddress,buf,BufLength,iDestinationPort);
	}
	ERROR_HANDLER_RETURN("Send",FALSE)
}

BOOL CUDPSocket::Send(int iSourcePort, 
					  LPCSTR lpDestinationAddress, 
					  int iDestinationPort,
					  const char* buf,
					  int BufLength)
{
	try
	{
		//Quit if not ok
		if (!CheckSocketValid())
			return FALSE;

		return Send(iSourcePort,inet_addr(lpDestinationAddress),iDestinationPort,buf,BufLength);
	}
	ERROR_HANDLER_RETURN("Send",FALSE)
}

BOOL CUDPSocket::CreateRegular()
{
	try
	{
		SetProtocol(IPPROTO_UDP);
		return CSpoofSocket::Create(IPPROTO_UDP);
	}
	ERROR_HANDLER_RETURN("CreateRegular",FALSE)
}

void CUDPSocket::FinalUDPHeader(LPUDPHeader lpHeader)
{
	//Nothing to do
}

KOMODIA_NAMESPACE_END
