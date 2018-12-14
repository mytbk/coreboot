/** @file
  This PPI provides a set of memory and I/O-based services. 
  The perspective of the services is that of the processor, not the bus or system.

Copyright (c) 2006 - 2010, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under 
the terms and conditions of the BSD License that accompanies this distribution.  
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.                                            

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

  @par Revision Reference:
  This PPI is introduced in PI Version 1.0.
  
**/

#ifndef __PEI_CPUIO_PPI_H__
#define __PEI_CPUIO_PPI_H__

#ifndef EFIAPI
#define EFIAPI __attribute((msabi))
#endif

#define EFI_PEI_CPU_IO_PPI_INSTALLED_GUID \
{ 0xe6af1f7b, 0xfc3f, 0x46da, {0xa8, 0x28, 0xa3, 0xb4, 0x57, 0xa4, 0x42, 0x82 } }

typedef struct _EFI_PEI_CPU_IO_PPI  EFI_PEI_CPU_IO_PPI;

///
/// EFI_PEI_CPU_IO_PPI_WIDTH.
///
typedef enum {
	EfiPeiCpuIoWidthUint8,
	EfiPeiCpuIoWidthUint16,
	EfiPeiCpuIoWidthUint32,
	EfiPeiCpuIoWidthUint64,
	EfiPeiCpuIoWidthFifoUint8,
	EfiPeiCpuIoWidthFifoUint16,
	EfiPeiCpuIoWidthFifoUint32,
	EfiPeiCpuIoWidthFifoUint64,
	EfiPeiCpuIoWidthFillUint8,
	EfiPeiCpuIoWidthFillUint16,
	EfiPeiCpuIoWidthFillUint32,
	EfiPeiCpuIoWidthFillUint64,
	EfiPeiCpuIoWidthMaximum
} EFI_PEI_CPU_IO_PPI_WIDTH;

/**
  Memory-based access services and I/O-based access services.

  @param[in]      PeiServices  An indirect pointer to the PEI Services Table
  published by the PEI Foundation.
  @param[in]      This         The pointer to local data for the interface.
  @param[in]      Width        The width of the access. Enumerated in bytes.
  @param[in]      Address      The physical address of the access.
  @param[in]      Count        The number of accesses to perform.
  @param[in, out] Buffer       A pointer to the buffer of data.

  @retval EFI_SUCCESS            The function completed successfully.
  @retval EFI_NOT_YET_AVAILABLE  The service has not been installed.

 **/
typedef
int
(EFIAPI *EFI_PEI_CPU_IO_PPI_IO_MEM)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		EFI_PEI_CPU_IO_PPI_WIDTH  Width,
		uint64_t                    Address,
		size_t                     Count,
		void                      *Buffer
		);

///
/// EFI_PEI_CPU_IO_PPI_ACCESS
///
typedef struct {
	///
	/// This service provides the various modalities of memory and I/O read.
	///
	EFI_PEI_CPU_IO_PPI_IO_MEM  Read;
	///
	/// This service provides the various modalities of memory and I/O write.
	///
	EFI_PEI_CPU_IO_PPI_IO_MEM  Write;
} EFI_PEI_CPU_IO_PPI_ACCESS;

/**
  8-bit I/O read operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.

  @return  An 8-bit value returned from the I/O space.

 **/
typedef
uint8_t
(EFIAPI *EFI_PEI_CPU_IO_PPI_IO_READ8)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address
		);

/**
  16-bit I/O read operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.

  @return  A 16-bit value returned from the I/O space.

 **/
typedef
uint16_t
(EFIAPI *EFI_PEI_CPU_IO_PPI_IO_READ16)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address
		);

/**
  32-bit I/O read operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.

  @return  A 32-bit value returned from the I/O space.

 **/
typedef
uint32_t
(EFIAPI *EFI_PEI_CPU_IO_PPI_IO_READ32)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address
		);

/**
  64-bit I/O read operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.

  @return  A 64-bit value returned from the I/O space.

 **/
typedef
uint64_t
(EFIAPI *EFI_PEI_CPU_IO_PPI_IO_READ64)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address
		);

/**
  8-bit I/O write operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.
  @param[in] Data         The data to write.

 **/
typedef
void
(EFIAPI *EFI_PEI_CPU_IO_PPI_IO_WRITE8)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address,
		uint8_t                     Data
		);

/**
  16-bit I/O write operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.
  @param[in] Data         The data to write.

 **/
typedef
void
(EFIAPI *EFI_PEI_CPU_IO_PPI_IO_WRITE16)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address,
		uint16_t                    Data
		);

/**
  32-bit I/O write operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.
  @param[in] Data         The data to write.

 **/
typedef
void
(EFIAPI *EFI_PEI_CPU_IO_PPI_IO_WRITE32)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address,
		uint32_t                    Data
		);

/**
  64-bit I/O write operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.
  @param[in] Data         The data to write.

 **/
typedef
void
(EFIAPI *EFI_PEI_CPU_IO_PPI_IO_WRITE64)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address,
		uint64_t                    Data
		);

/**
  8-bit memory read operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.

  @return  An 8-bit value returned from the memory space.

 **/
typedef
uint8_t
(EFIAPI *EFI_PEI_CPU_IO_PPI_MEM_READ8)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address
		);

/**
  16-bit memory read operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.

  @return  A 16-bit value returned from the memory space.

 **/
typedef
uint16_t
(EFIAPI *EFI_PEI_CPU_IO_PPI_MEM_READ16)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address
		);

/**
  32-bit memory read operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.

  @return  A 32-bit value returned from the memory space.

 **/
typedef
uint32_t
(EFIAPI *EFI_PEI_CPU_IO_PPI_MEM_READ32)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address
		);

/**
  64-bit memory read operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.

  @return  A 64-bit value returned from the memory space.

 **/
typedef
uint64_t
(EFIAPI *EFI_PEI_CPU_IO_PPI_MEM_READ64)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address
		);

/**
  8-bit memory write operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.
  @param[in] Data         The data to write.

 **/
typedef
void
(EFIAPI *EFI_PEI_CPU_IO_PPI_MEM_WRITE8)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address,
		uint8_t                     Data
		);

/**
  16-bit memory write operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.
  @param[in] Data         The data to write.

 **/
typedef
void
(EFIAPI *EFI_PEI_CPU_IO_PPI_MEM_WRITE16)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address,
		uint16_t                    Data
		);

/**
  32-bit memory write operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.
  @param[in] Data         The data to write.

 **/
typedef
void
(EFIAPI *EFI_PEI_CPU_IO_PPI_MEM_WRITE32)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address,
		uint32_t                    Data
		);

/**
  64-bit memory write operations.

  @param[in] PeiServices  An indirect pointer to the PEI Services Table published 
  by the PEI Foundation.
  @param[in] This         The pointer to local data for the interface.
  @param[in] Address      The physical address of the access.
  @param[in] Data         The data to write.

 **/
typedef
void
(EFIAPI *EFI_PEI_CPU_IO_PPI_MEM_WRITE64)(
		const EFI_PEI_SERVICES    **PeiServices,
		const EFI_PEI_CPU_IO_PPI  *This,
		uint64_t                    Address,
		uint64_t                    Data
		);

///
/// EFI_PEI_CPU_IO_PPI provides a set of memory and I/O-based services.
/// The perspective of the services is that of the processor, not that of the 
/// bus or system.
///
struct _EFI_PEI_CPU_IO_PPI {
	///
	/// Collection of memory-access services.
	///
	EFI_PEI_CPU_IO_PPI_ACCESS       Mem;
	///
	/// Collection of I/O-access services.
	///
	EFI_PEI_CPU_IO_PPI_ACCESS       Io;

	EFI_PEI_CPU_IO_PPI_IO_READ8     IoRead8;
	EFI_PEI_CPU_IO_PPI_IO_READ16    IoRead16;
	EFI_PEI_CPU_IO_PPI_IO_READ32    IoRead32;
	EFI_PEI_CPU_IO_PPI_IO_READ64    IoRead64;

	EFI_PEI_CPU_IO_PPI_IO_WRITE8    IoWrite8;
	EFI_PEI_CPU_IO_PPI_IO_WRITE16   IoWrite16;
	EFI_PEI_CPU_IO_PPI_IO_WRITE32   IoWrite32;
	EFI_PEI_CPU_IO_PPI_IO_WRITE64   IoWrite64;

	EFI_PEI_CPU_IO_PPI_MEM_READ8    MemRead8;
	EFI_PEI_CPU_IO_PPI_MEM_READ16   MemRead16;
	EFI_PEI_CPU_IO_PPI_MEM_READ32   MemRead32;
	EFI_PEI_CPU_IO_PPI_MEM_READ64   MemRead64;

	EFI_PEI_CPU_IO_PPI_MEM_WRITE8   MemWrite8;
	EFI_PEI_CPU_IO_PPI_MEM_WRITE16  MemWrite16;
	EFI_PEI_CPU_IO_PPI_MEM_WRITE32  MemWrite32;
	EFI_PEI_CPU_IO_PPI_MEM_WRITE64  MemWrite64;
};

extern EFI_GUID gEfiPeiCpuIoPpiInstalledGuid;

#endif
