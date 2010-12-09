/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2006 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.

You may alternatively use this source under the terms of a specific version of
the OGRE Unrestricted License provided you have obtained such a license from
Torus Knot Software Ltd.
-----------------------------------------------------------------------------
*/
#ifndef __CompositorManager_H__
#define __CompositorManager_H__

#include "OgrePrerequisites.h"
#include "OgreResourceManager.h"
#include "OgreCompositor.h"
#include "OgreRectangle2D.h"
#include "OgreCompositorSerializer.h"
#include "OgreRenderSystem.h"

namespace Ogre {
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Effects
	*  @{
	*/
	/** Class for managing Compositor settings for Ogre. Compositors provide the means
        to flexibly "composite" the final rendering result from multiple scene renders
        and intermediate operations like rendering fullscreen quads. This makes
        it possible to apply postfilter effects, HDRI postprocessing, and shadow
        effects to a Viewport.
        @par
            When loaded from a script, a Compositor is in an 'unloaded' state and only stores the settings
            required. It does not at that stage load any textures. This is because the material settings may be
            loaded 'en masse' from bulk material script files, but only a subset will actually be required.
        @par
            Because this is a subclass of ResourceManager, any files loaded will be searched for in any path or
            archive added to the resource paths/archives. See ResourceManager for details.
    */
    class _OgreExport CompositorManager : public ResourceManager, public Singleton<CompositorManager>
    {
    public:
        CompositorManager();
        virtual ~CompositorManager();

        /// Overridden from ResourceManager
        Resource* createImpl(const String& name, ResourceHandle handle,
            const String& group, bool isManual, ManualResourceLoader* loader,
            const NameValuePairList* params);

        /** Initialises the Compositor manager, which also triggers it to
            parse all available .compositor scripts. */
        void initialise(void);

        /** @see ScriptLoader::parseScript
        */
        void parseScript(DataStreamPtr& stream, const String& groupName);

        /** Get the compositor chain for a Viewport. If there is none yet, a new
			compositor chain is registered.
			XXX We need a _notifyViewportRemoved to find out when this viewport disappears,
			so we can destroy its chain as well.
        */
        CompositorChain *getCompositorChain(Viewport *vp);

		/** Returns whether exists compositor chain for a viewport.
        */
		bool hasCompositorChain(Viewport *vp) const;

		/** Remove the compositor chain from a viewport if exists.
		*/
        void removeCompositorChain(Viewport *vp);

		/** Add a compositor to a viewport. By default, it is added to end of the chain,
			after the other compositors.
			@param vp			Viewport to modify
			@param compositor	The name of the compositor to apply
			@param addPosition	At which position to add, defaults to the end (-1).
			@returns pointer to instance, or 0 if it failed.
		*/
		CompositorInstance *addCompositor(Viewport *vp, const String &compositor, int addPosition=-1);

		/** Remove a compositor from a viewport
		*/
		void removeCompositor(Viewport *vp, const String &compositor);

		/** Set the state of a compositor on a viewport to enabled or disabled.
			Disabling a compositor stops it from rendering but does not free any resources.
			This can be more efficient than using removeCompositor and addCompositor in cases
			the filter is switched on and off a lot.
		*/
		void setCompositorEnabled(Viewport *vp, const String &compositor, bool value);

		/** Get a textured fullscreen 2D rectangle, for internal use.
		*/
		Renderable *_getTexturedRectangle2D();

		/** Overridden from ResourceManager since we have to clean up chains too. */
		void removeAll(void);

		/** Internal method for forcing all active compositors to recreate their resources. */
		void _reconstructAllCompositorResources();

		typedef set<Texture*>::type UniqueTextureSet;

		/** Utility function to get an existing shared texture matching a given
			definition, or creating one if one doesn't exist. It also takes into
			account whether a shared texture has already been supplied to this
			same requester already, in which case it won't give the same texture
			twice (this is important for example if you request 2 ping-pong textures, 
			you don't want to get the same texture for both requests!
		*/
		TexturePtr getSharedTexture(const String& name, const String& localName, 
			size_t w, size_t h, 
			PixelFormat f, uint aa, const String& aaHint, bool srgb, UniqueTextureSet& texturesAlreadyAssigned, 
			CompositorInstance* inst);

		/** Free shared textures from the shared pool (compositor instances still 
			using them will keep them in memory though). 
		*/
		void freeSharedTextures(bool onlyIfUnreferenced = true);


		/** Override standard Singleton retrieval.
		@remarks
		Why do we do this? Well, it's because the Singleton
		implementation is in a .h file, which means it gets compiled
		into anybody who includes it. This is needed for the
		Singleton template to work, but we actually only want it
		compiled into the implementation of the class based on the
		Singleton, not all of them. If we don't change this, we get
		link errors when trying to use the Singleton-based class from
		an outside dll.
		@par
		This method just delegates to the template version anyway,
		but the implementation stays in this single compilation unit,
		preventing link errors.
		*/
		static CompositorManager& getSingleton(void);
		/** Override standard Singleton retrieval.
		@remarks
		Why do we do this? Well, it's because the Singleton
		implementation is in a .h file, which means it gets compiled
		into anybody who includes it. This is needed for the
		Singleton template to work, but we actually only want it
		compiled into the implementation of the class based on the
		Singleton, not all of them. If we don't change this, we get
		link errors when trying to use the Singleton-based class from
		an outside dll.
		@par
		This method just delegates to the template version anyway,
		but the implementation stays in this single compilation unit,
		preventing link errors.
		*/
		static CompositorManager* getSingletonPtr(void);

	
	private:
        typedef map<Viewport*, CompositorChain*>::type Chains;
        Chains mChains;

		/// Serializer - Hold instance per thread if necessary
		OGRE_THREAD_POINTER(CompositorSerializer, mSerializer);

        /** Clear composition chains for all viewports
         */
        void freeChains();

		Rectangle2D *mRectangle;

		/// List of instances
		typedef vector<CompositorInstance *>::type Instances;
		Instances mInstances;

		typedef vector<TexturePtr>::type TextureList;
		typedef VectorIterator<TextureList> TextureIterator;

		struct TextureDef
		{
			size_t width, height;
			PixelFormat format;
			uint fsaa;
			String fsaaHint;
			bool sRGBwrite;

			TextureDef(size_t w, size_t h, PixelFormat f, uint aa, const String& aaHint, bool srgb)
				: width(w), height(h), format(f), fsaa(aa), fsaaHint(aaHint), sRGBwrite(srgb)
			{

			}
		};
		struct TextureDefLess
		{
			bool _OgreExport operator()(const TextureDef& x, const TextureDef& y) const
			{
				if (x.format < y.format)
					return true;
				else if (x.format == y.format)
				{
					if (x.width < y.width)
						return true;
					else if (x.width == y.width)
					{
						if (x.height < y.height)
							return true;
						else if (x.height == y.height)
						{
							if (x.fsaa < y.fsaa)
								return true;
							else if (x.fsaa == y.fsaa)
							{
								if (x.fsaaHint < y.fsaaHint)
									return true;
								else if (x.fsaaHint == y.fsaaHint)
								{
									if (!x.sRGBwrite && y.sRGBwrite)
										return true;
								}

							}
						}
					}
				}
				return false;
			}
			virtual ~TextureDefLess() {}
		};
		typedef map<TextureDef, TextureList*, TextureDefLess>::type TexturesByDef;
		TexturesByDef mTexturesByDef;


		bool isInputPreviousTarget(CompositorInstance* inst, const Ogre::String& localName);
		bool isInputPreviousTarget(CompositorInstance* inst, TexturePtr tex);
		bool isInputToOutputTarget(CompositorInstance* inst, const Ogre::String& localName);
		bool isInputToOutputTarget(CompositorInstance* inst, TexturePtr tex);

    };
	/** @} */
	/** @} */

}

#endif
