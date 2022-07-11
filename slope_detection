#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/integral_image_normal.h>

/* Normal Estimation Using Integral Images
Since we are using a stereo camera and our dataset/pointcloud is organised, we can get faster results 
if we do the normal estimation by actually using the integral images. 


Choose a method for normal estimation

enum NormalEstimationMethod
{
  COVARIANCE_MATRIX,
  AVERAGE_3D_GRADIENT,
  AVERAGE_DEPTH_CHANGE
};

The COVARIANCE_MATRIX mode creates 9 integral images to compute the normal for a specific point
from the covariance matrix of its local neighborhood. The AVERAGE_3D_GRADIENT mode creates 6 
integral images to compute smoothed versions of horizontal and vertical 3D gradients and computes
the normals using the cross-product between these two gradients. The AVERAGE_DEPTH_CHANGE mode 
creates only a single integral image and computes the normals from the average depth changes.

In our case, AVERAGE_3D_GRADIENT will deliver the best results. 
This still needs to be verified with a rosbag!
*/



int 
main ()
{
    // load point cloud
    pcl::PointCloud<pcl::PointXYZ>::Ptr pointcloud (new pcl::PointCloud<pcl::PointXYZ>);
    
    // create object for the normal estimation and compute normals
    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);

    pcl::IntegralImageNormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
    ne.setNormalEstimationMethod (ne.AVERAGE_3D_GRADIENT);
    ne.setMaxDepthChangeFactor(0.02f);
    ne.setNormalSmoothingSize(10.0f);
    ne.setInputCloud(pointcloud);
    ne.compute(*normals);

    // visualize normals
    /*
    pcl::visualization::PCLVisualizer viewer("PCL Viewer");
    viewer.setBackgroundColor (0.0, 0.0, 0.5);
    viewer.addPointCloudNormals<pcl::PointXYZ,pcl::Normal>(pointcloud, normals);
    
    while (!viewer.wasStopped ())
    {
      viewer.spinOnce ();
    }
    return 0;
    */

    /* Calculate average slope
    Since we can only estimate very imprecisely where the slope will be on the road, we can't sample a group of vectors and calculate the slope with them. 
    However this is not a problem since we only need to know IF there is a surface curvature of any kind in front of us, which can be found
    by calculating the average slope on the road. 

    Might need to implement a threshold later, dont know the discrepancy yet. 

    Might also need to limit FOV later on.
    */


   /*
   //Below version uses surface_curvature property of pcl normal object, not sure if it is reliable enough, need to test it. 

    double surface_curvature = 0.0;
    int size = 0;

    for (const auto& normal : *normals) {

        surface_curvature += normal.curvature;
        size++;
    }

    double avg_surface_curvature = surface_curvature / size;

    return avg_surface_curvature;

   */


    double angle = 0.0;
    int size = 0;

    for (const auto& normal : *normals) {

        double dot_product = normal.x*0 + normal.y*0 + normal.z*1;
        double length_surface_vector = 1;
        double lenght_normal_vector = normal.x*normal.x + normal.y*normal.y + normal.z*normal.z;

        angle += acos(dot/sqrt(lenght_surface_vector * lenght_normal_vector));
        size++;
    }

    double avg_angle = angle / size;

    return avg_angle;

}

// Return average slope in front of us, not accurate but says IF there is a ramp 
