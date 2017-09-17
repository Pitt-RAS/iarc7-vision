// BAD HEADER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <cv_bridge/cv_bridge.h>
#pragma GCC diagnostic pop
// END BAD HEADER

#include <image_transport/image_transport.h>
#include <limits>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <iarc7_vision/VisionNodeConfig.h>

#include <sensor_msgs/image_encodings.h>

#include "iarc7_vision/GridLineEstimator.hpp"
#include "iarc7_vision/OpticalFlowEstimator.hpp"

void getDynamicSettings(iarc7_vision::VisionNodeConfig &config,
                        const ros::NodeHandle& private_nh,
                        iarc7_vision::LineExtractorSettings& line_settings,
                        iarc7_vision::OpticalFlowEstimatorSettings& flow_settings,
                        bool& ran)
{
    if (!ran) {
        // Begin line extractor settings
        ROS_ASSERT(private_nh.getParam(
                "line_extractor/pixels_per_meter",
                line_settings.pixels_per_meter));
        config.pixels_per_meter = line_settings.pixels_per_meter;

        ROS_ASSERT(private_nh.getParam(
                "line_extractor/canny_high_threshold",
                line_settings.canny_high_threshold));
        config.canny_high_threshold = line_settings.canny_high_threshold;

        double canny_threshold_ratio;
        ROS_ASSERT(private_nh.getParam(
                "line_extractor/canny_threshold_ratio",
                canny_threshold_ratio));
        line_settings.canny_low_threshold =
            line_settings.canny_high_threshold / canny_threshold_ratio;
        config.canny_threshold_ratio = canny_threshold_ratio;

        ROS_ASSERT(private_nh.getParam(
                "line_extractor/canny_sobel_size",
                line_settings.canny_sobel_size));
        config.canny_sobel_size = line_settings.canny_sobel_size;

        ROS_ASSERT(private_nh.getParam(
                "line_extractor/hough_rho_resolution",
                line_settings.hough_rho_resolution));
        config.hough_rho_resolution = line_settings.hough_rho_resolution;

        ROS_ASSERT(private_nh.getParam(
                "line_extractor/hough_theta_resolution",
                line_settings.hough_theta_resolution));
        config.hough_theta_resolution = line_settings.hough_theta_resolution;

        ROS_ASSERT(private_nh.getParam(
                "line_extractor/hough_thresh_fraction",
                line_settings.hough_thresh_fraction));
        config.hough_thresh_fraction = line_settings.hough_thresh_fraction;

        ROS_ASSERT(private_nh.getParam(
                "line_extractor/fov",
                line_settings.fov));
        config.fov = line_settings.fov;

        // Begin optical flow estimator settings
        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/pixels_per_meter",
                flow_settings.pixels_per_meter));
        config.flow_pixels_per_meter = flow_settings.pixels_per_meter;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/fov",
                flow_settings.fov));
        config.flow_fov = flow_settings.fov;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/min_estimation_altitude",
                flow_settings.min_estimation_altitude));
        config.flow_min_estimation_altitude = flow_settings.min_estimation_altitude;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/pixels_per_meter",
                flow_settings.pixels_per_meter));
        config.flow_pixels_per_meter = flow_settings.pixels_per_meter;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/points",
                flow_settings.points));
        config.flow_points = flow_settings.points;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/quality_level",
                flow_settings.quality_level));
        config.flow_quality_level = flow_settings.quality_level;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/min_dist",
                flow_settings.min_dist));
        config.flow_min_dist = flow_settings.min_dist;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/win_size",
                flow_settings.win_size));
        config.flow_win_size = flow_settings.win_size;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/max_level",
                flow_settings.max_level));
        config.flow_max_level = flow_settings.max_level;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/iters",
                flow_settings.iters));
        config.flow_iters = flow_settings.iters;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/scale_factor",
                flow_settings.scale_factor));
        config.flow_scale_factor = flow_settings.scale_factor;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/imu_update_timeout",
                flow_settings.imu_update_timeout));
        config.flow_imu_update_timeout = flow_settings.imu_update_timeout;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/variance",
                flow_settings.variance));
        config.flow_variance = flow_settings.variance;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/variance_scale",
                flow_settings.variance_scale));
        config.flow_variance_scale = flow_settings.variance_scale;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/x_cutoff_region_velocity_measurement",
                flow_settings.x_cutoff_region_velocity_measurement));
        config.flow_x_cutoff_region_velocity_measurement =
            flow_settings.x_cutoff_region_velocity_measurement;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/y_cutoff_region_velocity_measurement",
                flow_settings.y_cutoff_region_velocity_measurement));
        config.flow_y_cutoff_region_velocity_measurement =
            flow_settings.y_cutoff_region_velocity_measurement;

        ROS_ASSERT(private_nh.getParam(
                "optical_flow_estimator/debug_frameskip",
                flow_settings.debug_frameskip));
        config.flow_debug_frameskip = flow_settings.debug_frameskip;

        ran = true;
    } else {
        // Begin line extractor settings
        line_settings.pixels_per_meter = config.pixels_per_meter;
        line_settings.canny_high_threshold = config.canny_high_threshold;

        line_settings.canny_low_threshold =
            config.canny_high_threshold / config.canny_threshold_ratio;

        line_settings.canny_sobel_size = config.canny_sobel_size;
        line_settings.hough_rho_resolution = config.hough_rho_resolution;
        line_settings.hough_theta_resolution = config.hough_theta_resolution;
        line_settings.hough_thresh_fraction = config.hough_thresh_fraction;
        line_settings.fov = config.fov;

        // Begin optical flow estimator settings
        flow_settings.pixels_per_meter = config.flow_pixels_per_meter;
        flow_settings.fov = config.flow_fov;
        flow_settings.min_estimation_altitude = config.flow_min_estimation_altitude;
        flow_settings.points = config.flow_points;
        flow_settings.quality_level = config.flow_quality_level;
        flow_settings.min_dist = config.flow_min_dist;
        flow_settings.win_size = config.flow_win_size;
        flow_settings.max_level = config.flow_max_level;
        flow_settings.iters = config.flow_iters;
        flow_settings.scale_factor = config.flow_scale_factor;
        flow_settings.imu_update_timeout = config.flow_imu_update_timeout;
        flow_settings.variance = config.flow_variance;
        flow_settings.variance_scale = config.flow_variance_scale;
        flow_settings.x_cutoff_region_velocity_measurement =
            config.flow_x_cutoff_region_velocity_measurement;
        flow_settings.y_cutoff_region_velocity_measurement =
            config.flow_y_cutoff_region_velocity_measurement;
        flow_settings.debug_frameskip = config.flow_debug_frameskip;

    }
}

void getGridEstimatorSettings(const ros::NodeHandle& private_nh,
                              iarc7_vision::GridEstimatorSettings& settings)
{
    ROS_ASSERT(private_nh.getParam(
            "grid_estimator/theta_step",
            settings.theta_step));
    ROS_ASSERT(private_nh.getParam(
            "grid_estimator/grid_step",
            settings.grid_step));
    ROS_ASSERT(private_nh.getParam(
            "grid_estimator/grid_spacing",
            settings.grid_spacing));
    ROS_ASSERT(private_nh.getParam(
            "grid_estimator/grid_line_thickness",
            settings.grid_line_thickness));
    ROS_ASSERT(private_nh.getParam(
            "grid_estimator/grid_zero_offset_x",
            settings.grid_zero_offset(0)));
    ROS_ASSERT(private_nh.getParam(
            "grid_estimator/grid_zero_offset_y",
            settings.grid_zero_offset(1)));
    ROS_ASSERT(private_nh.getParam(
            "grid_estimator/grid_translation_mean_iterations",
            settings.grid_translation_mean_iterations));
    ROS_ASSERT(private_nh.getParam(
            "grid_estimator/line_rejection_angle_threshold",
            settings.line_rejection_angle_threshold));
    ROS_ASSERT(private_nh.getParam(
            "grid_estimator/min_extraction_altitude",
            settings.min_extraction_altitude));
    ROS_ASSERT(private_nh.getParam(
            "grid_estimator/allowed_position_stamp_error",
            settings.allowed_position_stamp_error));
}

void getGridDebugSettings(const ros::NodeHandle& private_nh,
                      iarc7_vision::GridLineDebugSettings& settings)
{
   ROS_ASSERT(private_nh.getParam(
            "grid_line_estimator/debug_line_detector",
            settings.debug_line_detector));
    ROS_ASSERT(private_nh.getParam(
            "grid_line_estimator/debug_direction",
            settings.debug_direction));
    ROS_ASSERT(private_nh.getParam(
            "grid_line_estimator/debug_edges",
            settings.debug_edges));
    ROS_ASSERT(private_nh.getParam(
            "grid_line_estimator/debug_lines",
            settings.debug_lines));
    ROS_ASSERT(private_nh.getParam(
            "grid_line_estimator/debug_line_markers",
            settings.debug_line_markers));
    if (private_nh.hasParam("grid_line_estimator/debug_height")) {
        ROS_ASSERT(private_nh.getParam(
            "grid_line_estimator/debug_height",
            settings.debug_height));
    } else {
        settings.debug_height = std::numeric_limits<double>::quiet_NaN();
    }
}

void getFlowDebugSettings(const ros::NodeHandle& private_nh,
                          iarc7_vision::OpticalFlowDebugSettings& settings)
{
    ROS_ASSERT(private_nh.getParam(
            "optical_flow_estimator/debug_vectors_image",
            settings.debug_vectors_image));

    ROS_ASSERT(private_nh.getParam(
        "optical_flow_estimator/debug_average_vector_image",
        settings.debug_average_vector_image));

    ROS_ASSERT(private_nh.getParam(
        "optical_flow_estimator/debug_times",
        settings.debug_times));
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "vision");

    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");

    // Create dynamic reconfigure server and settings callback
    dynamic_reconfigure::Server<iarc7_vision::VisionNodeConfig> dynamic_reconfigure_server;
    iarc7_vision::OpticalFlowEstimatorSettings optical_flow_estimator_settings;
    iarc7_vision::LineExtractorSettings line_extractor_settings;
    bool dynamic_reconfigure_called = false;

    boost::function<void(iarc7_vision::VisionNodeConfig &config,
                         uint32_t level)> dynamic_reconfigure_settings_callback =
        [&](iarc7_vision::VisionNodeConfig &config, uint32_t) {
            getDynamicSettings(config,
                               private_nh,
                               line_extractor_settings,
                               optical_flow_estimator_settings,
                               dynamic_reconfigure_called);
        };

    dynamic_reconfigure_server.setCallback(dynamic_reconfigure_settings_callback);

    // Create and load grid estimator settings
    iarc7_vision::GridEstimatorSettings grid_estimator_settings;
    getGridEstimatorSettings(private_nh, grid_estimator_settings);
    iarc7_vision::GridLineDebugSettings grid_line_debug_settings;
    getGridDebugSettings(private_nh, grid_line_debug_settings);
    iarc7_vision::GridLineEstimator gridline_estimator(
            line_extractor_settings,
            grid_estimator_settings,
            grid_line_debug_settings);

    // Create and load optical flow debug settings
    iarc7_vision::OpticalFlowDebugSettings optical_flow_debug_settings;
    getFlowDebugSettings(private_nh, optical_flow_debug_settings);
    iarc7_vision::OpticalFlowEstimator optical_flow_estimator(
            nh,
            optical_flow_estimator_settings,
            optical_flow_debug_settings);

    // Check for images at 100 Hz
    ros::Rate rate (100);

    // Wait for time to begin
    while (ros::ok() &&
           (ros::Time::now() == ros::Time(0) ||
           !dynamic_reconfigure_called)) {
        // wait
        ros::spinOnce();
    }

    // Load the parameters specific to the vision node
    double startup_timeout;
    ROS_ASSERT(private_nh.getParam("startup_timeout", startup_timeout));

    int message_queue_item_limit;
    ROS_ASSERT(private_nh.getParam("message_queue_item_limit", message_queue_item_limit));

    // Initialize the vision classes
    ROS_ASSERT(gridline_estimator.waitUntilReady(ros::Duration(startup_timeout)));
    ROS_ASSERT(optical_flow_estimator.waitUntilReady(ros::Duration(startup_timeout)));


    // Queue and callback for collecting images
    std::vector<sensor_msgs::Image::ConstPtr> message_queue;

    std::function<void(const sensor_msgs::Image::ConstPtr&)> handler =
        [&](const sensor_msgs::Image::ConstPtr& message) {
            message_queue.push_back(message);
        };

    image_transport::ImageTransport image_transporter{nh};
    ros::Subscriber sub = nh.subscribe(
        "/bottom_image_raw/image_raw",
        100,
        &std::function<void(const sensor_msgs::Image::ConstPtr&)>::operator(),
        &handler);

    // Main loop
    while (ros::ok())
    {
        if (message_queue.size() > 0) {

            sensor_msgs::Image::ConstPtr message;
            if (static_cast<int>(message_queue.size()) > message_queue_item_limit) {
                ROS_ERROR("Image queue has too many messages, clearing: %d images", (int)message_queue.size());

                message = message_queue.back();
                message_queue.clear();
            }
            else {
                message = message_queue.front();
                message_queue.erase(message_queue.begin());
            }

            // Don't use the gridline estimator right now for speed reasons
            gridline_estimator.update(cv_bridge::toCvShare(message)->image,
                                      message->header.stamp);

            optical_flow_estimator.update(message);
        }

        ros::spinOnce();
        rate.sleep();
    }

    // All is good.
    return 0;
}
