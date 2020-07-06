

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Jun 24 16:18:16 2020
 */
/* Compiler settings for EasyPlayerProActiveX.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __EasyPlayerProActiveXidl_h__
#define __EasyPlayerProActiveXidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DEasyPlayerProActiveX_FWD_DEFINED__
#define ___DEasyPlayerProActiveX_FWD_DEFINED__
typedef interface _DEasyPlayerProActiveX _DEasyPlayerProActiveX;
#endif 	/* ___DEasyPlayerProActiveX_FWD_DEFINED__ */


#ifndef ___DEasyPlayerProActiveXEvents_FWD_DEFINED__
#define ___DEasyPlayerProActiveXEvents_FWD_DEFINED__
typedef interface _DEasyPlayerProActiveXEvents _DEasyPlayerProActiveXEvents;
#endif 	/* ___DEasyPlayerProActiveXEvents_FWD_DEFINED__ */


#ifndef __EasyPlayerProActiveX_FWD_DEFINED__
#define __EasyPlayerProActiveX_FWD_DEFINED__

#ifdef __cplusplus
typedef class EasyPlayerProActiveX EasyPlayerProActiveX;
#else
typedef struct EasyPlayerProActiveX EasyPlayerProActiveX;
#endif /* __cplusplus */

#endif 	/* __EasyPlayerProActiveX_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __EasyPlayerProActiveXLib_LIBRARY_DEFINED__
#define __EasyPlayerProActiveXLib_LIBRARY_DEFINED__

/* library EasyPlayerProActiveXLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_EasyPlayerProActiveXLib;

#ifndef ___DEasyPlayerProActiveX_DISPINTERFACE_DEFINED__
#define ___DEasyPlayerProActiveX_DISPINTERFACE_DEFINED__

/* dispinterface _DEasyPlayerProActiveX */
/* [uuid] */ 


EXTERN_C const IID DIID__DEasyPlayerProActiveX;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4FEB3DC3-9794-4E94-A928-05E02BADE855")
    _DEasyPlayerProActiveX : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DEasyPlayerProActiveXVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DEasyPlayerProActiveX * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DEasyPlayerProActiveX * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DEasyPlayerProActiveX * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DEasyPlayerProActiveX * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DEasyPlayerProActiveX * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DEasyPlayerProActiveX * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DEasyPlayerProActiveX * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DEasyPlayerProActiveXVtbl;

    interface _DEasyPlayerProActiveX
    {
        CONST_VTBL struct _DEasyPlayerProActiveXVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DEasyPlayerProActiveX_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DEasyPlayerProActiveX_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DEasyPlayerProActiveX_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DEasyPlayerProActiveX_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DEasyPlayerProActiveX_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DEasyPlayerProActiveX_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DEasyPlayerProActiveX_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DEasyPlayerProActiveX_DISPINTERFACE_DEFINED__ */


#ifndef ___DEasyPlayerProActiveXEvents_DISPINTERFACE_DEFINED__
#define ___DEasyPlayerProActiveXEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DEasyPlayerProActiveXEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DEasyPlayerProActiveXEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("194E1B18-4C63-4155-9783-EB383F95DFFD")
    _DEasyPlayerProActiveXEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DEasyPlayerProActiveXEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DEasyPlayerProActiveXEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DEasyPlayerProActiveXEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DEasyPlayerProActiveXEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DEasyPlayerProActiveXEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DEasyPlayerProActiveXEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DEasyPlayerProActiveXEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DEasyPlayerProActiveXEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DEasyPlayerProActiveXEventsVtbl;

    interface _DEasyPlayerProActiveXEvents
    {
        CONST_VTBL struct _DEasyPlayerProActiveXEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DEasyPlayerProActiveXEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DEasyPlayerProActiveXEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DEasyPlayerProActiveXEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DEasyPlayerProActiveXEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DEasyPlayerProActiveXEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DEasyPlayerProActiveXEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DEasyPlayerProActiveXEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DEasyPlayerProActiveXEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_EasyPlayerProActiveX;

#ifdef __cplusplus

class DECLSPEC_UUID("C826A1CE-34E6-4BB1-B844-681E7AC98D9A")
EasyPlayerProActiveX;
#endif
#endif /* __EasyPlayerProActiveXLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


