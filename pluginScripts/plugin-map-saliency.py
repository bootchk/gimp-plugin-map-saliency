#!/usr/bin/env python

'''
Gimp plugin "Map saliency"

Derived by:
- substitutinginto gimp-plugin-engine-template,
- augmenting.

Copyright 2016 lloyd konneker (bootch at nc.rr.com)

License:

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  The GNU Public License is available at
  http://www.gnu.org/copyleft/gpl.html

'''

from gimpfu import *

gettext.install("map-saliency", gimp.locale_directory, unicode=True)



def doFoo(timg, tdrawable):  # , fooParam=50):
  '''
  Adapt to an inner plugin engine.
  '''
  # typical GUI preamble
  # We are not changing timg, disable undo
  pdb.gimp_image_undo_disable(timg)
  
  # Result is a new, copy of image
  resultImage = pdb.gimp_image_duplicate(timg)
  if not resultImage:
      raise RuntimeError, "Failed duplicate image"

  # Need drawable as parameter to inner engine
  resultDrawable = pdb.gimp_image_get_active_drawable(resultImage)
  if not resultDrawable:
      raise RuntimeError, "Failed get active drawable"
  
  if pdb.gimp_drawable_has_alpha(resultDrawable):
      # eliminate alpha channel not expected by inner engine
      # Note resultDrawable may change
      resultDrawable = pdb.gimp_image_flatten(resultImage);
  
  # convert copy image to grayscale required by inner engine
  if not pdb.gimp_drawable_is_gray(resultDrawable) :
      pdb.gimp_image_convert_grayscale(resultImage)
  
  # Call wrapped, C-language, engine plugin
  # !!! Method name matches PROCEDURE_NAME that C-language engine registered
  # PyGimp creates methods of pdb object dynamically at GIMP start time
  pdb.gimp_plugin_engine_saliency(resultImage, resultDrawable, 1)  # 1 is param not used 
  
  # This displays an alert dialog, but doesn't wait until dialog is acknowledged.
  # pdb.gimp_message(_("Python engine template ran."))
  
  
  # Display result image in new window
  gimp.Display(resultImage) 
  gimp.displays_flush()
  
  # Postlude, opposite of prelude
  pdb.gimp_image_undo_enable(timg)
  



# This mostly defines GUI for the plugin
# Note it is internationalized il8n
register(
  "python_fu_map_saliency",  #< PDB procedure name
  N_("Create gray map of saliency."), #< blurb
  "Saliency is human focus.  Requires OpenCV libs.",   #< help
  "Lloyd Konneker",       #< Author
  "2016 Lloyd Konneker",  #< Copyright holder
  "2016",
  N_("_Saliency"),    #< menu item
  "RGB*, GRAY*, INDEXED*",
  [
    (PF_IMAGE, "image",       "Input image", None),
    (PF_DRAWABLE, "drawable", "Input drawable", None),
    # (PF_INT, "fooParam", _("Foo:"), 50),    #<
  ],
  [],
  doFoo,    # Python method that implements plugin
  menu="<Image>/Filters/Map",  #< parent menu
  domain=("map-saliency", gimp.locale_directory)
  )

main()

