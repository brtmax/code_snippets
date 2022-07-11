// 3D pointcloud RANSAC plane fitting
// Author: Max Bretschneider


 
    pcl::PointCloud<pcl::PointXYZ> project_cloud_to_ground(pcl::PointCloud<pcl::PointXYZ> pointcloud) {

        

    // Surface mesh ?


    //- -------------------------- Plane ----------------------- ---------- 

    pcl::SACSegmentation<pcl::PointXYZ> sac;
    pcl::ModelCoefficients::Ptr coefficients(newpcl::ModelCoefficients);
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane(new pcl::PointCloud<pcl::PointXYZ);

    sac.setInputCloud(pointcloud);
    sac.setMethodType(pcl::SAC_RANSAC);
    sac.setModelType(pcl::SACMODEL_PLANE);
    sac.setDistanceThreshold(15); // Distance needs to be adjusted according to the object
    sac.setMaxIterations(100);
    sac.setProbability(0.95);
    sac.segment(*inliers, *coefficients);

    boost::shared_ptr<pcl::visualization::PCLVisualizer> view(new pcl::visualization::PCLVisualizer>); view->addPointCloud(pointcloud);

    // Plane Model ax + by + cz + d = 0, saved in *coefficients

    float a,b,c,d;

    a = coefficients->values[0];
    b = coefficients->values[1];
    c = coefficients->values[2];
    d = coefficients->values[3];

    int i,j,k;

    int size = pointcloud->size();

    // Projection 
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane(new pcl::PointCloud<pcl::PointXYZ>); 
    pcl::PointXYZ point; 

    for (i = 0; i < size; i++) {

        float x,y,z;

        x = pointcloud->at(i).x;
        y = pointcloud->at(i).y;
        z = pointcloud->at(i).z;

        point.x = ((b*b + c*c)*x-a*(b*y + c*z + d))/(a*a + b*b + c *c); 
        point.y = ((a*a + c*c)*y-b*(a*x + c*z + d))/(a*a + b*b + c*c); 
        point.z = ((b*b + a*a)*z-c*(a*x + b*y + d))/(a*a + b*b + c*c); 

        cloud_plane->push_back(point);
    }

    return cloud_plane;
}
